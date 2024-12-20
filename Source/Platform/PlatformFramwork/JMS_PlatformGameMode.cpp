// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_PlatformGameMode.h"

#include "JMS_PlatformCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"


AJMS_PlatformGameMode::AJMS_PlatformGameMode()
{
	
}

void AJMS_PlatformGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (NewPlayer)
	{
		AllPlayerControllers.Add(NewPlayer);
		
	}
}

void AJMS_PlatformGameMode::Logout(AController* Exiting)
{
	if (APlayerController* PC = Cast<APlayerController>(Exiting))
	{
		AllPlayerControllers.Remove(PC);
	}

	// Logout할때 해당 Controller를 삭제하는 동작이 있기에 먼저 배열에서 삭제를 진행한다.
	Super::Logout(Exiting);


}

void AJMS_PlatformGameMode::SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC)
{
	Super::SwapPlayerControllers(OldPC, NewPC);

	if (NewPC)
	{
		AllPlayerControllers.Add(NewPC);
		
	}
}

void AJMS_PlatformGameMode::EnableCharacterMovement_Implementation()
{
}

/*
void AJMS_PlatformGameMode::EnableCharacterMovement()
{
	for (APlayerController* PlayerCharacterController : AllPlayerControllers)
	{
		APawn* PawnChar = PlayerCharacterController->GetPawn();
		if (AJMS_PlatformCharacter* NewCharacter = Cast<AJMS_PlatformCharacter>(PawnChar))
		{
			NewCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Walking,0);
		}
		

	}
}
*/

