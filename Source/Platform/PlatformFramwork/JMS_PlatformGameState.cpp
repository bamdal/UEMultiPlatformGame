// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_PlatformGameState.h"

#include "JMS_PlatformGameMode.h"
#include "JMS_PlatformPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"


void AJMS_PlatformGameState::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		GetWorld()->GetTimerManager().SetTimer(CountdownTimerHandle, this, &ThisClass::CountDownProc, 1.0f, true);
	}
}

void AJMS_PlatformGameState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);
}

void AJMS_PlatformGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, RoundCountDown);
	DOREPLIFETIME(ThisClass, IsRoundEnded);
	DOREPLIFETIME(ThisClass, WinnerRef);
}


void AJMS_PlatformGameState::OnRep_RoundCountDown()
{
	// 카운트 다운
	// 레디고 애니메이션
	PlayCountdownSound();
	PlayReadyGoAnimation();

	if (HasAuthority())
	{
		if (RoundCountDown == 0)
		{
			// 게임시작
			GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);
			StartRound();
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Round countdown started");
		}
	}
}

void AJMS_PlatformGameState::OnRep_IsRoundEnded()
{
	if (SB_RefereeWhistle)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), SB_RefereeWhistle);
	}

	AJMS_PlatformPlayerController* Controller = Cast<AJMS_PlatformPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (Controller)
	{
		Controller->MatchOver();
	}
}

void AJMS_PlatformGameState::OnRep_WinnerRef()
{
	if (HasAuthority())
	{
		IsRoundEnded = true;
	}
	OnRep_IsRoundEnded();
}

void AJMS_PlatformGameState::SetWinnerRef(APlayerState* Winner)
{
	WinnerRef = Winner;
	if (HasAuthority())
	{
		OnRep_WinnerRef();
	}
}


// 게임 시작 처리
void AJMS_PlatformGameState::StartRound()
{
	AJMS_PlatformGameMode* GM = Cast<AJMS_PlatformGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GM)
	{
		GM->EnableCharacterMovement();
	}
}

void AJMS_PlatformGameState::CountDownProc()
{
	if (HasAuthority())
	{
		--RoundCountDown;
		OnRep_RoundCountDown();
	}
}

void AJMS_PlatformGameState::PlayCountdownSound()
{
	if (RoundCountDown > 0)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), SB_Countdown);
	}
	else if (RoundCountDown == 0)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), SB_CountdownFinal);
	}
}

void AJMS_PlatformGameState::PlayReadyGoAnimation()
{
	// 2초 남았을 때
	if (RoundCountDown == 2)
	{
		AJMS_PlatformPlayerController* Controller = Cast<AJMS_PlatformPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (Controller)
		{
			Controller->ReadyGo();
		}
	}
}
