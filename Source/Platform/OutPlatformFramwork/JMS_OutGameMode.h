// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "JMS_OutGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORM_API AJMS_OutGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AJMS_OutGameMode();

protected:
	virtual void BeginPlay() override;	
};
