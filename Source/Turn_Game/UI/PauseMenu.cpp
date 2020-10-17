// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"
#include "SubMenuParty.h"
void UPauseMenu::ViewPartyMenu()
{
	if (PartyMenuClass)
	{
		PartyMenu = Cast<USubMenuParty>(CreateWidget<UUserWidget>(this, PartyMenuClass));
		PartyMenu->ConstructSubWidget();
		PartyMenu->AddToViewport();
		PartyMenu->SetVisibility(ESlateVisibility::Visible);
	}
}
