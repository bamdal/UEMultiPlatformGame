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
	

	
public:

	UPROPERTY(BlueprintReadWrite,Replicated,Category=Appearance)
	int32 PlayerColorID = 0;

	UPROPERTY(BlueprintReadWrite,Replicated,Category=Appearance)
	bool InitAppearance = false;

	// null이면 시작지점 스폰, 또는 체크포인트 지점 tag에서 생성
	UPROPERTY(BlueprintReadWrite,Replicated,Category=CheckPoint)
	FName CheckPointTag;

protected:
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
};
