// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "JMS_PlatformGameMode.generated.h"

namespace EDrawDebugTrace
{
	enum Type : int;
}

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

public:
	UPROPERTY(BlueprintReadWrite)
	TArray<APlayerController*> AllPlayerControllers;

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
	virtual void SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC) override;


public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EnableCharacterMovement();


};
