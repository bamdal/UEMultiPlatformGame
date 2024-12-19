// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JMS_WidgetBasicButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonClickedDelegate);
/**
 * 
 */
UCLASS()
class PLATFORM_API UJMS_WidgetBasicButton : public UUserWidget
{
	GENERATED_BODY()


public:

	//변수 --------------------
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float SBWidth = 355.0f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float SBHeight = 42.0f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UTexture2D> NormalImage;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UTexture2D> HoveredImage;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UTexture2D> PressedImage;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FLinearColor FontColor;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 FontSize = 16;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FText ButtonText ;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName Typeface = TEXT("Bold");

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TEnumAsByte<EHorizontalAlignment> Btn_HorizontalAlignment = HAlign_Center;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FMargin Btn_Padding;
	
	// UI ------------------------------------------

	UPROPERTY(BlueprintReadWrite,meta=(BindWidget))
	TObjectPtr<class USizeBox> SB_SizeBox;

	UPROPERTY(BlueprintReadWrite,meta=(BindWidget))
	TObjectPtr<class UTextBlock> TB_TextBlock;

	UPROPERTY(BlueprintReadWrite,meta=(BindWidget))
	TObjectPtr<class UButton> B_Button;

	// delegate
	UPROPERTY(BlueprintAssignable,Category="Events")
	FOnButtonClickedDelegate B_BaseDelegate;

public:

	UFUNCTION(BlueprintCallable,Category="Events")
	void OnClickedBase();

	UFUNCTION(BlueprintCallable,Category="Events")
	void SetBaseButtonText(FString& Str);
	
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

protected:
	void Setup();
	void SetFont();
	void SetButtonSize();
	void SetButtonStyle();
};
