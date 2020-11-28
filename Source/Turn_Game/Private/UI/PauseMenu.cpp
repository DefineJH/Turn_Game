// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/UI/PauseMenu.h"
#include "../Public/UI/SubMenuParty.h"
#include "../Public/UI/SubMenuSave.h"
#include "../Public/UI/SubMenuInventory.h"
#include "Components/Button.h"

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
	this->AddToViewport(0);
	SetFocus();
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
		PartyMenu->ConstructSubWidget();
	}
	if (SaveMenuClass)
	{
		SaveMenu = Cast<USubMenuSave>(CreateWidget<UUserWidget>(this, SaveMenuClass));
		SaveMenu->ConstructSubWidget();
	}
	if (InvenMenuClass)
	{
		InvenMenu = Cast<USubMenuInventory>(CreateWidget<UUserWidget>(this, InvenMenuClass));
		InvenMenu->ConstructSubWidget();
	}
	return true;
}

void UPauseMenu::ViewPartyMenu()
{
	this->RemoveFromViewport();
	PartyMenu->AddToViewport(1);
	PartyMenu->SetVisibility(ESlateVisibility::Visible);
	CurrentMenu = PartyMenu;
	UpdateCurMenu();
}

void UPauseMenu::ViewSaveMenu()
{
	this->RemoveFromViewport();
	SaveMenu->AddToViewport(1);
	SaveMenu->SetVisibility(ESlateVisibility::Visible);
	CurrentMenu = SaveMenu;
	UpdateCurMenu();
}

void UPauseMenu::ViewInvenMenu()
{
	this->RemoveFromViewport();
	InvenMenu->AddToViewport(1);
	InvenMenu->SetVisibility(ESlateVisibility::Visible);
	CurrentMenu = InvenMenu;
	UpdateCurMenu();
}

void UPauseMenu::DisableFocus()
{
	PartyBtn->IsFocusable = false;
}

void UPauseMenu::SetFocus()
{
	if (PartyBtn)
	{
		UE_LOG(LogTemp, Warning, L"BtnAble");
		PartyBtn->SetKeyboardFocus();
	}
}

void UPauseMenu::UpdateCurMenu()
{
	CurrentMenu->UpdateSubWidget();
}
