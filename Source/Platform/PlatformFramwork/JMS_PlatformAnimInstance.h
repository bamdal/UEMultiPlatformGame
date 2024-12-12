// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "JMS_PlatformAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORM_API UJMS_PlatformAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	APawn* Owner;
	
	UPROPERTY()
	UPawnMovementComponent* MovementComponent;

	UPROPERTY(BlueprintReadWrite)
	bool IsInAir;

	UPROPERTY(BlueprintReadWrite)
	bool IsMovementInput;
	
	UPROPERTY(BlueprintReadWrite)
	FRotator CurrentRotation;

	UPROPERTY(BlueprintReadWrite)
	FRotator PreviousRotation;

	UPROPERTY(BlueprintReadWrite)
	float LeanAmount;

	UPROPERTY(BlueprintReadWrite)
	float GroundSpeed;
	
	UPROPERTY(BlueprintReadWrite)
	float VelocityZ;

public:
	UFUNCTION()
	float GetVelocityZ() const { return VelocityZ; }


protected:

	UFUNCTION()
	virtual void NativeBeginPlay() override;
	
	UFUNCTION()
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION()
	void CalcLean(float DeltaSeconds);
	
	// 로코모션은 많은 CPU자원을 먹기에 Thread로 작업하는게 요즘 추세
	// virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
};
