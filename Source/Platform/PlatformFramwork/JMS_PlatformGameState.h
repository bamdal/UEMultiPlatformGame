// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "JMS_PlatformGameState.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORM_API AJMS_PlatformGameState : public AGameState
{
	GENERATED_BODY()


public:
	
	UPROPERTY(BlueprintReadWrite,ReplicatedUsing = OnRep_RoundCountDown,Category="Round")
	int32 RoundCountDown = 0;

	UPROPERTY(BlueprintReadWrite,ReplicatedUsing = OnRep_IsRoundEnded,Category="Round")
	bool IsRoundEnded = false;
	
	UPROPERTY(BlueprintReadWrite,ReplicatedUsing = OnRep_WinnerRef)
	APlayerState* WinnerRef;

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

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION()
	virtual void OnRep_RoundCountDown();

	UFUNCTION()
	virtual void OnRep_IsRoundEnded();

	UFUNCTION()
	virtual void OnRep_WinnerRef();
public:
	UFUNCTION(BlueprintCallable)
	void SetWinnerRef(APlayerState* Winner);
	
	UFUNCTION()
	void StartRound();
	UFUNCTION()
	void CountDownProc();
	UFUNCTION()
	void PlayCountdownSound();
	UFUNCTION()
	void PlayReadyGoAnimation();
};
