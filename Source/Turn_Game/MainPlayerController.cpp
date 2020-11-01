// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "UI/PauseMenu.h"
#include "Blueprint/UserWidget.h"

void AMainPlayerController::BeginPlay()
{
	if (WPauseMenu)
	{
		PauseMenu = Cast<UPauseMenu>(CreateWidget<UUserWidget>(this, WPauseMenu));
		if (PauseMenu)
		{
			PauseMenu->AddToViewport();
			PauseMenu->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void AMainPlayerController::SetUIInput()
{
	SetInputMode(FInputModeGameAndUI());
	bShowMouseCursor = true;
}

void AMainPlayerController::SetGameInput()
{
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}

void AMainPlayerController::DisplayPauseMenu()
{
	SetUIInput();
	PauseMenu->SetVisibility(ESlateVisibility::Visible);
}

void AMainPlayerController::RemovePauseMenu()
{
	SetGameInput();
	PauseMenu->SetVisibility(ESlateVisibility::Hidden);
}



void AMainPlayerController::Back()
{
	if (!PauseMenu)
		DisplayPauseMenu();
	else
	{
		if (PauseMenu->GetIsRoot())
		{
			RemovePauseMenu();
		}
		else
			PauseMenu->RemoveSubMenu();
	}
}

void AMainPlayerController::UpdateWidget()
{
	if (PauseMenu)
	{
		PauseMenu->UpdateCurMenu();
	}
}


