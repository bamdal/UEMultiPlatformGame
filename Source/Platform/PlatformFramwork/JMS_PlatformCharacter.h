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

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Landed(const FHitResult& Hit);
	virtual void FellOutOfWorld(const UDamageType& DmgType) override;


public:

};
