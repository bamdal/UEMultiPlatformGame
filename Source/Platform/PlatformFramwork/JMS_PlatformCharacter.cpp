// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_PlatformCharacter.h"

#include "JMS_PlatformAnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"

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


void AJMS_PlatformCharacter::FellOutOfWorld(const class UDamageType& dmgType)
{
	//Super::FellOutOfWorld(dmgType);

	if (HasAuthority() || GetLocalRole() == ROLE_None)
	{
		GetCapsuleComponent()->SetSimulatePhysics(true);
		GetMesh()->SetSimulatePhysics(true);
		GetCameraBoom()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

		LookAtTarget();
	}
}

void AJMS_PlatformCharacter::LookAtTarget()
{
	FVector VStart = (GetActorLocation() - GetFollowCamera()->GetComponentLocation());
	VStart.Normalize();
	FRotator LookAt = VStart.Rotation();
	GetFollowCamera()->SetWorldRotation(LookAt);

	// 경과 시간 업데이트
	ElapsedTime += GetWorld()->GetDeltaSeconds();

	// 3초가 지나면 타이머 정리
	if (ElapsedTime >= TimerDuration)
	{
		AController* BackupController = Controller;
		Destroy();
		AGameMode* MyGameMode = GetWorld()->GetAuthGameMode<AGameMode>();
		if(MyGameMode)
		{


			MyGameMode->RestartPlayer(BackupController);
		
		}
	}
}
