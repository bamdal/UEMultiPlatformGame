// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "JMS_PlatformPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORM_API AJMS_PlatformPlayerState : public APlayerState
{
	GENERATED_BODY()
	
	
protected:
	
	UPROPERTY(Replicated,BlueprintReadOnly)
	int32 Pickups;
	
public:
	void AddPickup()
	{
		Pickups++;
		GEngine->AddOnScreenDebugMessage(-1,3.0f,FColor::Red,FString::Printf(TEXT("%s : %s Pickups: %d"),*this->GetName(),*GetOwner()->GetName(),Pickups));
	};

	int32 GetPickups() const {return Pickups;};
};
