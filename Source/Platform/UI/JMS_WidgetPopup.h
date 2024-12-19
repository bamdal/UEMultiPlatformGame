// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JMS_WidgetPopup.generated.h"

class UTextBlock;
class UJMS_WidgetBasicButton;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonOKClicked);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonCancelClicked);

UCLASS()
class PLATFORM_API UJMS_WidgetPopup : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UJMS_WidgetBasicButton> WBP_Button_Confirm;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UJMS_WidgetBasicButton> WBP_Button_Decline;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UTextBlock> TB_Popup_Text;

	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn))
	FText PopupMessage;
	
	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn))
	FText ConfirmButtonText;
	
	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn))
	FText DeclineButtonText;
	
	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn))
	bool bShowRightButton;

	// delegate -------------------

	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnButtonOKClicked OnButtonOKClickedDelegate;

	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnButtonCancelClicked OnButtonCancelClickedDelegate;

public:
	UFUNCTION(BlueprintCallable)
	void OnClickedOKBtn();

	UFUNCTION(BlueprintCallable)
	void OnClickedCancelBtn();

protected:
	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;
};
