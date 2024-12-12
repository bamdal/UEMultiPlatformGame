// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_PlatformAnimInstance.h"

#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UJMS_PlatformAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Owner = Cast<APawn>(TryGetPawnOwner());
	if (Owner == nullptr)
	{
		return;
	}

	MovementComponent = Owner->GetMovementComponent();

}

void UJMS_PlatformAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);


	if (Owner == nullptr)
	{
		return;
	}

	if (MovementComponent == nullptr)
	{
		return;
	}
	if (Owner)
	{
		IsInAir = MovementComponent->IsFalling();

		const FVector2D VelocityXY =  FVector2D(MovementComponent->Velocity.X, MovementComponent->Velocity.Y);
		GroundSpeed = VelocityXY.Length();
		
		VelocityZ = MovementComponent->Velocity.Z;

		CalcLean(DeltaSeconds);
		
		IsMovementInput = Owner->GetLastMovementInputVector().Length() > 0;
	}
}

void UJMS_PlatformAnimInstance::CalcLean(const float DeltaSeconds)
{
	CurrentRotation = Owner->GetActorRotation();
	
	FRotator Delta = PreviousRotation - CurrentRotation;
	Delta.Normalize(); // == FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(PreviousRotation, CurrentRotation);
	
	LeanAmount = FMath::FInterpTo(LeanAmount,Delta.Yaw,DeltaSeconds,5.0f);
	//GEngine->AddOnScreenDebugMessage(-1,0.1f,FColor::Red, FString::Printf(TEXT("%s"),*Delta.ToString()));

	PreviousRotation = Owner->GetActorRotation();

		
	
}
