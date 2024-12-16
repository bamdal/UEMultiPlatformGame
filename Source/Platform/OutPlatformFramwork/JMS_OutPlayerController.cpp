// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_OutPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"


AJMS_OutPlayerController::AJMS_OutPlayerController()
{
	// 마우스 활성화
	this->SetShowMouseCursor(true);
}

void AJMS_OutPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(IsLocalController() && MainMenuClass != nullptr)
	{
		MainMenu = CreateWidget<UUserWidget>(this, MainMenuClass);
		if(MainMenu != nullptr)
		{
			MainMenu->AddToViewport();

			// UI만 사용자 입력에 응답할 수 있도록 입력 모드를 설정합니다. 참고: 즉, 위젯의 바운드 입력 이벤트는 호출되지 않습니다!
			// 마우스 커서를 UI에 잠그지 않는다
			UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(this,MainMenu,EMouseLockMode::DoNotLock);
			//bShowMouseCursor = true;

			// 네트워크 에러 판별 코드 추가
		}
	}

	
}
