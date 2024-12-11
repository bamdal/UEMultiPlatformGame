// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_PlatformCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AJMS_PlatformCharacter::AJMS_PlatformCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(35.f, 60.0f);
		
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 900.f;
	GetCharacterMovement()->AirControl = 0.25f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;


}

void AJMS_PlatformCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void AJMS_PlatformCharacter::BeginPlay()
{
	Super::BeginPlay();

	
}

void AJMS_PlatformCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}

void AJMS_PlatformCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
}

void AJMS_PlatformCharacter::FellOutOfWorld(const UDamageType& DmgType)
{
	Super::FellOutOfWorld(DmgType);
}
