// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "JMS_OutPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORM_API AJMS_OutPlayerController : public APlayerController
{
	GENERATED_BODY()

	AJMS_OutPlayerController();
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Widget)
	TSubclassOf<class UUserWidget> MainMenuClass;

	UPROPERTY()
	class UUserWidget* MainMenu;
protected:
	virtual void BeginPlay() override;
};
