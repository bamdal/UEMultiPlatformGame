// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "JMS_PlatformPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORM_API AJMS_PlatformPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ReadyGo();


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void MatchOver();

	



protected:
	virtual void BeginPlay() override;
};
