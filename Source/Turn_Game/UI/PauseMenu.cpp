// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"
#include "SubMenuParty.h"
#include "SubMenuSave.h"

bool UPauseMenu::GetIsRoot()
{
	if (CurrentMenu)
		return false;
	else
		return true;
}

void UPauseMenu::RemoveSubMenu()
{
	CurrentMenu->RemoveFromViewport();
	CurrentMenu = nullptr;
}

bool UPauseMenu::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	if (PartyMenuClass)
	{
		PartyMenu = Cast<USubMenuParty>(CreateWidget<UUserWidget>(this, PartyMenuClass));
	}
	if (SaveMenuClass)
	{
		SaveMenu = Cast<USubMenuSave>(CreateWidget<UUserWidget>(this, SaveMenuClass));
	}
	return true;
}

void UPauseMenu::ViewPartyMenu()
{
	PartyMenu->ConstructSubWidget();
	PartyMenu->AddToViewport(1);
	PartyMenu->SetVisibility(ESlateVisibility::Visible);
	CurrentMenu = PartyMenu;
}

void UPauseMenu::ViewSaveMenu()
{
	SaveMenu->ConstructSubWidget();
	SaveMenu->AddToViewport(1);
	SaveMenu->SetVisibility(ESlateVisibility::Visible);
	CurrentMenu = SaveMenu;
}

void UPauseMenu::UpdateCurMenu()
{
	CurrentMenu->UpdateSubWidget();
}
