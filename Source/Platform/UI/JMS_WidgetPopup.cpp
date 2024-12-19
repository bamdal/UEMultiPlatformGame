// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS_WidgetPopup.h"

#include "JMS_WidgetBasicButton.h"
#include "Components/TextBlock.h"


void UJMS_WidgetPopup::NativePreConstruct()
{
	Super::NativePreConstruct();

	if(TB_Popup_Text)
	{
		TB_Popup_Text->SetText(PopupMessage);
		
	}
	if (WBP_Button_Confirm && WBP_Button_Confirm->TB_TextBlock)
	{
		WBP_Button_Confirm->TB_TextBlock->SetText(ConfirmButtonText);
	}
	
	
	if (WBP_Button_Decline)
	{
		if (bShowRightButton)
		{
			WBP_Button_Decline->SetVisibility(ESlateVisibility::Visible);
			if (WBP_Button_Decline->TB_TextBlock)
			{
				WBP_Button_Decline->TB_TextBlock->SetText(DeclineButtonText);
			}
		}
		else
		{
			WBP_Button_Decline->SetVisibility(ESlateVisibility::Collapsed);
			
		}
	}

	
}


void UJMS_WidgetPopup::NativeConstruct()
{
	Super::NativeConstruct();

	if (WBP_Button_Confirm)
	{
		WBP_Button_Confirm->B_BaseDelegate.AddDynamic(this,&ThisClass::OnClickedOKBtn);
	}
	if (WBP_Button_Decline)
	{
		WBP_Button_Decline->B_BaseDelegate.AddDynamic(this,&ThisClass::OnClickedCancelBtn);
		
	}
}

void UJMS_WidgetPopup::NativeDestruct()
{
	Super::NativeDestruct();
	WBP_Button_Confirm->B_BaseDelegate.RemoveDynamic(this,&ThisClass::OnClickedCancelBtn);
	WBP_Button_Decline->B_BaseDelegate.RemoveDynamic(this,&ThisClass::OnClickedCancelBtn);

	
}


void UJMS_WidgetPopup::OnClickedOKBtn()
{
	RemoveFromParent();
	OnButtonOKClickedDelegate.Broadcast();
}

void UJMS_WidgetPopup::OnClickedCancelBtn()
{
	RemoveFromParent();
	OnButtonCancelClickedDelegate.Broadcast();
}
