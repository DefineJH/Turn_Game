// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/UI/PauseMenu.h"
#include "../Public/UI/SubMenuParty.h"
#include "../Public/UI/SubMenuSave.h"
#include "../Public/UI/SubMenuInventory.h"

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
	if (InvenMenuClass)
	{
		InvenMenu = Cast<USubMenuInventory>(CreateWidget<UUserWidget>(this, InvenMenuClass));
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

void UPauseMenu::ViewInvenMenu()
{
	InvenMenu->ConstructSubWidget();
	InvenMenu->AddToViewport(1);
	InvenMenu->SetVisibility(ESlateVisibility::Visible);
	CurrentMenu = InvenMenu;
}

void UPauseMenu::UpdateCurMenu()
{
	CurrentMenu->UpdateSubWidget();
}
