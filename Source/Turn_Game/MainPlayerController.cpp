// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "Blueprint/UserWidget.h"
void AMainPlayerController::BeginPlay()
{
	if (WPauseMenu)
	{
		PauseMenu = CreateWidget<UUserWidget>(this, WPauseMenu);
		if (PauseMenu)
		{
			PauseMenu->AddToViewport();
			PauseMenu->SetVisibility(ESlateVisibility::Hidden);
			bPauseMenuVisibility = false;
		}
	}
	if (WPartyMenu)
	{
		PartyMenu = CreateWidget<UUserWidget>(this, WPartyMenu);
		if (PartyMenu)
		{
			PartyMenu->AddToViewport();
			PartyMenu->SetVisibility(ESlateVisibility::Hidden);
			bPartyMenuVisibility = false;
		}
	}
}

void AMainPlayerController::SetUIInput()
{
	SetInputMode(FInputModeUIOnly());
}

void AMainPlayerController::SetGameInput()
{
	SetInputMode(FInputModeGameOnly());
}

void AMainPlayerController::DisplayPauseMenu()
{
	SetUIInput();
	bPauseMenuVisibility = true;
	PauseMenu->SetVisibility(ESlateVisibility::Visible);
	overlayDepth++;
}

void AMainPlayerController::RemovePauseMenu()
{
	bPauseMenuVisibility = false;
	PauseMenu->SetVisibility(ESlateVisibility::Hidden);
	overlayDepth--;
	if (overlayDepth == 0)
	{
		SetGameInput();
	}
}

void AMainPlayerController::DisplayPartyMenu()
{
	overlayDepth++;
	RemovePauseMenu();
}

void AMainPlayerController::Back()
{

}

void AMainPlayerController::RemovePartyMenu()
{
	overlayDepth--;
	DisplayPauseMenu();
}

//void AMainPlayerController::TogglePauseMenu()
//{
//	if (!bPauseMenuVisibility)
//		DisplayPauseMenu();
//	else
//		RemovePauseMenu();
//}
//
//void AMainPlayerController::TogglePartyMenu()
//{
//	if (!bPartyMenuVisibility)
//		DisplayPartyMenu();
//	else
//		RemovePartyMenu();
//}
