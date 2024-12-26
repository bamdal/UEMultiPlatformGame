// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_PlatformGameState.h"

#include "JMS_PlatformGameMode.h"
#include "JMS_PlatformPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"


void AJMS_PlatformGameState::BeginPlay()
{
	Super::BeginPlay();
	
	
	// 서버만 카운트 다운 시작
	if (HasAuthority())
	{
		ServerCountDownProc();
		NM_SetGamePlayTypes(EJMS_GamePlay::GameInit);

	}
	
	if (GamePlayTypes == EJMS_GamePlay::None)
	{
		GamePlayTypes =EJMS_GamePlay::GameInit;
	}
}

void AJMS_PlatformGameState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);
}



void AJMS_PlatformGameState::NM_RoundCountdown_Implementation(int32 Count)
{
	RoundCountDown = Count;
	
	// 카운트 다운 사운드 출력
	PlayCountdownSound();
	// 레디고 애니메이션
	PlayReadyGoAnimation();
	
}

void AJMS_PlatformGameState::NM_IsRoundEnded_Implementation(APlayerState* WinnerPS)
{
	WinnerRef = WinnerPS;
	
	
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

// 게임 시작 처리
void AJMS_PlatformGameState::ServerStartRound()
{
	AJMS_PlatformGameMode* GM = Cast<AJMS_PlatformGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GM)
	{
		GM->EnableCharacterMovement();
	}
}





void AJMS_PlatformGameState::ServerPlayerWinner(APlayerState* WinnerPS)
{
	if (HasAuthority())
	{
		
		NM_SetGamePlayTypes(EJMS_GamePlay::GameResult);
		NM_IsRoundEnded(WinnerPS);
	}


}




void AJMS_PlatformGameState::ServerCountDownProc()
{
	NM_SetGamePlayTypes(EJMS_GamePlay::ReadyCountdown);
	//RoundCountDown = 0; // 이런 값들은 ini에서 값 가져와서 config 처리 해야함

	auto CountDownDelegate = [this](/* 파라미터 값 */)
	{
		if (IsValid(this))
		{
			--RoundCountDown;	// 서버만 감소
			NM_RoundCountdown(RoundCountDown);	// 감소한 값을 NetMulticast로 전송
			if (RoundCountDown == 0)
			{
				// 게임시작
				GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);
				ServerStartRound();
				NM_SetGamePlayTypes(EJMS_GamePlay::GamePlaying);

				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Round countdown started");
			}
		}
	};
	
	GetWorld()->GetTimerManager().SetTimer(CountdownTimerHandle, CountDownDelegate, 1.0f, true);
	
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

void AJMS_PlatformGameState::NM_SetGamePlayTypes_Implementation(EJMS_GamePlay GameType)
{
	GamePlayTypes = GameType;
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan,FString::Printf(TEXT("Set Type %s"), *StaticEnum<EJMS_GamePlay>()->GetNameByIndex(static_cast<uint8>(GamePlayTypes)).ToString() ));

}

