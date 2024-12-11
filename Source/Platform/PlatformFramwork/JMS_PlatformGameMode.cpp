// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_PlatformGameMode.h"

#include "JMS_PlatformGameState.h"

AJMS_PlatformGameMode::AJMS_PlatformGameMode()
{
	
}

void AJMS_PlatformGameMode::BeginPlay()
{
	Super::BeginPlay();

	CoinGameState = GetGameState<AJMS_PlatformGameState>();
}
