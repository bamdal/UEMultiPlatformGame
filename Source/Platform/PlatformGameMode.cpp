// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlatformGameMode.h"
#include "PlatformCharacter.h"
#include "UObject/ConstructorHelpers.h"

APlatformGameMode::APlatformGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
