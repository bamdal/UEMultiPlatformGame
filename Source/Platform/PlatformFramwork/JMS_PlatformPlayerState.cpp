// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_PlatformPlayerState.h"

#include "Net/UnrealNetwork.h"


void AJMS_PlatformPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		PlayerColorID = FMath::RandRange(0,4);
		InitAppearance = true;
	}
}

void AJMS_PlatformPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AJMS_PlatformPlayerState, PlayerColorID);
	DOREPLIFETIME(AJMS_PlatformPlayerState, InitAppearance);
	DOREPLIFETIME(AJMS_PlatformPlayerState, CheckPointTag);
}


