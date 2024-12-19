// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_WidgetBasicButton.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/ButtonSlot.h"


void UJMS_WidgetBasicButton::NativePreConstruct()
{
	Super::NativePreConstruct();

	Setup();
}

void UJMS_WidgetBasicButton::NativeConstruct()
{
	Super::NativeConstruct();

	if (B_Button)
	{
		
		//B_Button->OnClicked.Clear();

		B_Button->OnClicked.AddDynamic(this,&ThisClass::OnClickedBase);
	}
}

void UJMS_WidgetBasicButton::NativeDestruct()
{
	Super::NativeDestruct();
	B_Button->OnClicked.RemoveDynamic(this,&ThisClass::OnClickedBase);
}

void UJMS_WidgetBasicButton::OnClickedBase()
{

	B_BaseDelegate.Broadcast();
}

void UJMS_WidgetBasicButton::SetBaseButtonText(FString& Str)
{
	if (TB_TextBlock)
	{
		TB_TextBlock->SetText(FText::FromString(Str));
	}
}


void UJMS_WidgetBasicButton::Setup()
{
	SetFont();
	SetButtonSize();
	SetButtonStyle();
}

void UJMS_WidgetBasicButton::SetFont()
{
	if (TB_TextBlock == nullptr)
	{
		return;
	}

	// 폰트 객체 로드
	
	UObject* FontObject = LoadObject<UObject>(nullptr,TEXT("/Engine/EngineFonts/Roboto"));
	if (FontObject == nullptr)
	{
		UE_LOG(LogTemp,Error,TEXT("UJMS_BasicButton::SetFont Failed Load FontObject"));
		return;
	}
	FSlateFontInfo NewFontInfo(FontObject,FontSize,Typeface);
	
	TB_TextBlock->SetFont(NewFontInfo);
	TB_TextBlock->SetText(ButtonText);
	TB_TextBlock->SetColorAndOpacity(FSlateColor(FontColor));
}

void UJMS_WidgetBasicButton::SetButtonSize()
{
	if (SB_SizeBox ==nullptr)
	{
		return;
	}
	SB_SizeBox->SetWidthOverride(SBWidth);
	SB_SizeBox->SetHeightOverride(SBHeight);
}

void UJMS_WidgetBasicButton::SetButtonStyle()
{
	if (B_Button == nullptr)
	{
		return;
	}

	// 버튼 스타일
	FButtonStyle NewButtonStyle;

	// 버튼 기능별 슬레이트 브러시
	if (NormalImage)
	{
		FSlateBrush Brush;	// normal
		Brush.DrawAs = ESlateBrushDrawType::Box;
		Brush.SetResourceObject(NormalImage);
		NewButtonStyle.SetNormal(Brush);
	}

	if (HoveredImage)
	{
		FSlateBrush Brush;	// Hovered
		Brush.DrawAs = ESlateBrushDrawType::Box;
		Brush.SetResourceObject(HoveredImage);
		NewButtonStyle.SetHovered(Brush);
	}

	if (PressedImage)
	{
		FSlateBrush Brush;	// Pressed
		Brush.DrawAs = ESlateBrushDrawType::Box;
		Brush.SetResourceObject(PressedImage);
		NewButtonStyle.SetPressed(Brush);
	}

	FButtonStyle CurrentStyle = B_Button->GetStyle();
	NewButtonStyle.SetDisabled(CurrentStyle.Disabled);
	NewButtonStyle.SetNormalPadding(CurrentStyle.NormalPadding);
	NewButtonStyle.SetPressedPadding(CurrentStyle.PressedPadding);
	NewButtonStyle.SetPressedSound(CurrentStyle.PressedSlateSound);
	NewButtonStyle.SetHoveredSound(CurrentStyle.HoveredSlateSound);
	
	B_Button->SetStyle(NewButtonStyle);

	UButtonSlot* B_ButtonSlot = Cast<UButtonSlot>(B_Button->GetContentSlot());
	if (B_ButtonSlot != nullptr)
	{
		B_ButtonSlot->SetHorizontalAlignment(Btn_HorizontalAlignment);
		B_ButtonSlot->SetPadding(Btn_Padding);
	}
	
}
