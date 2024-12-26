// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystem.h"
#include "../Character/JMSCharBase.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "JMS_PlatformCharacter.generated.h"

/**
 * 
 */

UCLASS()
class PLATFORM_API AJMS_PlatformCharacter : public AJMSCharBase
{
	GENERATED_BODY()
	
public:
	AJMS_PlatformCharacter();
	virtual void PostInitializeComponents() override;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* IA_Pause;

private:

	float TimerDuration = 5.0f; // 타이머 지속 시간
	float ElapsedTime = 0.0f;   // 경과 시간 추적
	
public:
	UFUNCTION()
	void UpdateSmoothingCamera(float DeltaTime);

	UFUNCTION()
	void Pause(const FInputActionValue& Value);
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;



public:
	// TSharedPtr<IOnlineSession, ESPMode::ThreadSafe>
	IOnlineSessionPtr OnlineSessionInterface; // (스팀) 온라인 서브시스템 인터페이스

protected:
	// 클라가 세션을 생성하는 명령
	UFUNCTION(BlueprintCallable)
	void CreateGameSession();

	UFUNCTION(BlueprintCallable)
	void FindAndJoinGameSession();

	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionsComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName Name, EOnJoinSessionCompleteResult::Type Arg);
	
private:
	FOnCreateSessionCompleteDelegate CreateSessionCompleteDelegate;
	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	FOnJoinSessionCompleteDelegate JoinSessionCompleteDelegate;
};
