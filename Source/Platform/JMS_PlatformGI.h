// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "JMS_PlatformGI.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORM_API UJMS_PlatformGI : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite,Category = "JMSError Handling")
	FString JMSNetworkError;	// 넷드라이버의 통신에러
	
	UPROPERTY(BlueprintReadWrite,Category = "JMSError Handling")
	FString JMSTravelError;	// 서브 트래블 에러
};
