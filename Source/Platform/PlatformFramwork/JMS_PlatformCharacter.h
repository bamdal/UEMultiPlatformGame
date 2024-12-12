// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Character/JMSCharBase.h"
#include "JMS_PlatformCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORM_API AJMS_PlatformCharacter : public AJMSCharBase
{
	GENERATED_BODY()
	
public:
	AJMS_PlatformCharacter();
	virtual void PostInitializeComponents() override;

private:

	float TimerDuration = 5.0f; // 타이머 지속 시간
	float ElapsedTime = 0.0f;   // 경과 시간 추적
	
public:
	UFUNCTION()
	void UpdateSmoothingCamera(float DeltaTime);

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void FellOutOfWorld(const class UDamageType& dmgType) override;

public:

	void LookAtTarget();
};
