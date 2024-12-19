// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_PlatformGameState.h"

#include "Net/UnrealNetwork.h"


void AJMS_PlatformGameState::BeginPlay()
{
	Super::BeginPlay();

}

void AJMS_PlatformGameState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AJMS_PlatformGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass,RoundCountDown);
	DOREPLIFETIME(ThisClass,IsRoundEnded);
	DOREPLIFETIME(ThisClass,WinnerRef);
}


void AJMS_PlatformGameState::OnRep_RoundCountDown()
{
	// 카운트 다운
	// 레디고 애니메이션

	if (HasAuthority())
	{
		if (RoundCountDown ==0)
		{
			// 게임시작
		}
	}
}

void AJMS_PlatformGameState::OnRep_IsRoundEnded()
{
}

void AJMS_PlatformGameState::OnRep_WinnerRef()
{
}



void AJMS_PlatformGameState::CountDownProc()
{
	auto CountDownDelegate = [this]()
	{
		if (IsValid(this))
		{
			--RoundCountDown;
		}
	};
	GetWorld()->GetTimerManager().SetTimer(CountdownTimerHandle,CountDownDelegate,1.0f,false);
}
