// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "JMS_PlatformGameMode.generated.h"

class AJMS_PlatformPlayerState;
class AJMS_PlatformGameState;
/**
 * 
 */
//UCLASS(config = CoinGameRule)
UCLASS(config = Game)
class PLATFORM_API AJMS_PlatformGameMode : public AGameMode
{
	GENERATED_BODY()

	AJMS_PlatformGameMode();

protected:
	UPROPERTY()
	AJMS_PlatformGameState* CoinGameState;

protected:
	virtual void BeginPlay() override;


};
