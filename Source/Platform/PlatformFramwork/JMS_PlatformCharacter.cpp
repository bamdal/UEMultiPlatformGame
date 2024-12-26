// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_PlatformCharacter.h"

#include "EnhancedInputComponent.h"
#include "JMS_PlatformAnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

class AGameMode;

AJMS_PlatformCharacter::AJMS_PlatformCharacter() 
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(35.f, 60.0f);

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 900.f;
	GetCharacterMovement()->AirControl = 0.25f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

//------------------------------------------------------------------
	
	CreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &ThisClass::OnCreateSessionComplete);
	FindSessionsCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject(this,&ThisClass::OnFindSessionsComplete);
	JoinSessionCompleteDelegate = FOnJoinSessionCompleteDelegate::CreateUObject(this,&ThisClass::OnJoinSessionComplete);

	
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		OnlineSessionInterface = OnlineSubsystem->GetSessionInterface();
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue,
				FString::Printf(TEXT("Found subsystem %s"), *OnlineSubsystem->GetSubsystemName().ToString()));
		}
	}
}

void AJMS_PlatformCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}


void AJMS_PlatformCharacter::BeginPlay()
{
	Super::BeginPlay();

	
}

void AJMS_PlatformCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateSmoothingCamera(DeltaSeconds);
}

void AJMS_PlatformCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}


void AJMS_PlatformCharacter::UpdateSmoothingCamera(float DeltaTime)
{
	FVector VStart = GetActorLocation();
	TArray<AActor*> ActorToIgnore;
	ActorToIgnore.Add(this);
	
	FHitResult HitResult;
	bool bHit = UKismetSystemLibrary::LineTraceSingle(GetWorld(), VStart,VStart + FVector(0,0,250.0f),
	                                      UEngineTypes::ConvertToTraceType(ECC_Camera), false, ActorToIgnore,
	                                      EDrawDebugTrace::None, HitResult, true);
	if(HitResult.GetActor() != nullptr)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, HitResult.GetActor()->GetName());
	float Target = 300.0f;
	if (!bHit)
	{
		Target = GetCharacterMovement()->IsFalling() ? 1000.0f : 600.0f;
	}
	GetCameraBoom()->TargetArmLength = FMath::FInterpTo(GetCameraBoom()->TargetArmLength, Target, DeltaTime, 5.0f);
}




void AJMS_PlatformCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(IA_Pause,ETriggerEvent::Triggered,this,&ThisClass::Pause);

	}
}


void AJMS_PlatformCharacter::Pause(const FInputActionValue& Value)
{
}

//====================================================================


// 키보드 1
void AJMS_PlatformCharacter::CreateGameSession()
{
	if (!OnlineSessionInterface.IsValid())
	{
		return;
	}
	// 기존에 세션이 존재하는지 확인
	FNamedOnlineSession* ExistingSession = OnlineSessionInterface->GetNamedSession(NAME_GameSession);
	if (ExistingSession)
	{
		OnlineSessionInterface->DestroySession(NAME_GameSession);
	}

	OnlineSessionInterface->AddOnCreateSessionCompleteDelegate_Handle(CreateSessionCompleteDelegate);

	TSharedPtr<FOnlineSessionSettings> SessionSettings = MakeShareable(new FOnlineSessionSettings());
	SessionSettings->bIsLANMatch = false;			// LAN 컨넥션
	SessionSettings->NumPublicConnections = 4;		// 세션 참여 인원
	SessionSettings->bAllowJoinInProgress = true;	// 세션 실행중에 다른 유저가 조인할 수있는지
	SessionSettings->bAllowJoinViaPresence = true;	// 내 근처에 있는 유저 우선
	SessionSettings->bShouldAdvertise = true;		// 세션 광고 여부
	SessionSettings->bUsesPresence = true;			// 내가 있는 지역에서 진행중인 세션 검색
	SessionSettings->bUseLobbiesIfAvailable = true;	// 대상 플랫폼이 로비 API를 지원할 떄 그 로비 API를 사용할 것인지

	
	SessionSettings->Set(FName("MatchType"), FString("FreeForAll"),EOnlineDataAdvertisementType::ViaPingOnly);
	
	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	OnlineSessionInterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(),NAME_GameSession,*SessionSettings);
}

// 2
void AJMS_PlatformCharacter::FindAndJoinGameSession()
{
	if (!OnlineSessionInterface.IsValid())
	{
		return;
	}

	OnlineSessionInterface->AddOnFindSessionsCompleteDelegate_Handle(FindSessionsCompleteDelegate);
	
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->MaxSearchResults = 100;
	SessionSearch->bIsLanQuery = false;
	SessionSearch->QuerySettings.Set(TEXT("PRESENCESEARCH"),true,EOnlineComparisonOp::Equals);	// 5.5.1 에서 부터바뀜

	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	OnlineSessionInterface->FindSessions(*LocalPlayer->GetPreferredUniqueNetId(),SessionSearch.ToSharedRef());
	
}

// (스팀) 세션 생성 완료시 호출
void AJMS_PlatformCharacter::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1,15.0f,FColor::Blue,FString::Printf(TEXT("Create Session %s"),*SessionName.ToString()));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1,15.0f,FColor::Red,FString::Printf(TEXT("Fail Session %s"),*SessionName.ToString()));
	}
}

void AJMS_PlatformCharacter::OnFindSessionsComplete(bool bWasSuccessful)
{
	for (auto Element : SessionSearch->SearchResults)
	{
		GEngine->AddOnScreenDebugMessage(-1,15.0f,FColor::Red,FString::Printf(TEXT("%s"),*Element.Session.OwningUserName));

		FString ID = Element.GetSessionIdStr();
		FString User = Element.Session.OwningUserName;
		FString MatchType;
		Element.Session.SessionSettings.Get(FName("MatchType"),MatchType);
		
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan,
				FString::Printf(TEXT("Find Session [ ID: %s / User: %s ]"), *ID, *User));

			OnlineSessionInterface->AddOnJoinSessionCompleteDelegate_Handle(JoinSessionCompleteDelegate);

			// 테스트용 바로진입
			const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
			OnlineSessionInterface->JoinSession(*LocalPlayer->GetPreferredUniqueNetId(),NAME_GameSession,Element);
		}
	}

}

void AJMS_PlatformCharacter::OnJoinSessionComplete(FName Name, EOnJoinSessionCompleteResult::Type Arg)
{
	if (!OnlineSessionInterface.IsValid())
	{
		return;
	}

	FString Address;
	if (OnlineSessionInterface->GetResolvedConnectString(NAME_GameSession,Address))
	{
		GEngine->AddOnScreenDebugMessage(-1,15.0f,FColor::Cyan,FString::Printf(TEXT("Connect Address : %s"),*Address));
		APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
		if (PlayerController)
		{
			PlayerController->ClientTravel(Address,TRAVEL_Absolute);
		}
		
	}
}
