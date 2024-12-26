// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "JMS_PlatformGameState.generated.h"

// 게임의 진행상태를 나타내기위한 Enum값
UENUM(BlueprintType)
enum class EJMS_GamePlay : uint8
{
	None = 0,
	GameInit,
	ReadyCountdown,
	GamePlaying,
	GameResult,
};

/**
 * 
 */
UCLASS()
class PLATFORM_API AJMS_PlatformGameState : public AGameState
{
	GENERATED_BODY()


public:
	
	UPROPERTY(BlueprintReadWrite,Category=Round)
	int32 RoundCountDown = 0;

	UPROPERTY(BlueprintReadWrite,Category=GameEnd)
	APlayerState* WinnerRef;

	UPROPERTY(BlueprintReadWrite)
	EJMS_GamePlay GamePlayTypes = EJMS_GamePlay::None;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sound")
	TObjectPtr<USoundBase> SB_Countdown;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sound")
	TObjectPtr<USoundBase> SB_CountdownFinal;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sound")
	TObjectPtr<USoundBase> SB_RefereeWhistle;

	FTimerHandle CountdownTimerHandle;
	
protected:
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UFUNCTION(NetMulticast,Reliable)
	void NM_RoundCountdown(int32 Count);

	UFUNCTION(NetMulticast,Reliable)
	void NM_IsRoundEnded(APlayerState* WinnerPS);
	
	UFUNCTION(BlueprintCallable)
	void ServerPlayerWinner(APlayerState* WinnerPS);
	
public:

	UFUNCTION()
	void ServerStartRound();
	UFUNCTION()
	void ServerCountDownProc();
	UFUNCTION()
	void PlayCountdownSound();
	UFUNCTION()
	void PlayReadyGoAnimation();

	UFUNCTION(NetMulticast,Reliable)
	void NM_SetGamePlayTypes(EJMS_GamePlay GameType);
};
