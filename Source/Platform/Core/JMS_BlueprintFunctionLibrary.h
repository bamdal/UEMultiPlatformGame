// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JMS_BlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORM_API UJMS_BlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "JMSError Handling",meta=(WorldContext = "WorldContextObject"))
	static bool IsActiveError(const UObject* WorldContextObject);
	
	
};
