// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_PlatformPlayerState.h"

#include "Net/UnrealNetwork.h"

void AJMS_PlatformPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AJMS_PlatformPlayerState,Pickups);
}
