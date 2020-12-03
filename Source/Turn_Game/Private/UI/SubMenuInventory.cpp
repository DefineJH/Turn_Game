// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/UI/SubMenuInventory.h"
#include "../Public/UI/InvenView.h"
#include "../Public/Custom/CusomEnum.h"
#include "Components/WidgetSwitcher.h"
#include <Components/TextBlock.h>
#include <../GI_Archive.h>
#include <Components/Button.h>

void USubMenuInventory::SetInitalFocus()
{
	UInvenView* currentView = Cast<UInvenView>(ListCategory[CurrentPage]);
	currentView->SetFocus();
}

void USubMenuInventory::ConstructSubWidget()
{
	CurrentPage = 0;
	MaxPage = (uint8)EItemType::EIT_MAX;

	NextBtn->OnClicked.AddDynamic(this, &USubMenuInventory::NextPage);
	PrevBtn->OnClicked.AddDynamic(this, &USubMenuInventory::PrevPage);

	for (uint8 i = 0; i < MaxPage; i++)
	{
		UInvenView* singleInven = Cast<UInvenView>(CreateWidget<UUserWidget>(this, InvenClass));

		singleInven->ConstructList((EItemType)i);
		if (singleInven)
		{
			ListCategory.Add(singleInven);
			Switcher->AddChild(singleInven);
		}
	}
	ShowPage();
}

void USubMenuInventory::UpdateSubWidget()
{

}

void USubMenuInventory::NextPage()
{
	if (CurrentPage < MaxPage - 1)
		CurrentPage++;
	ShowPage();
}

void USubMenuInventory::PrevPage()
{
	if (CurrentPage > 0)
		CurrentPage--;
	ShowPage();
}

void USubMenuInventory::ShowPage()
{
	Category->SetText(FText::FromString(UGI_Archive::GetFStringFromEnum("EItemType", CurrentPage)));
	Switcher->SetActiveWidgetIndex(CurrentPage);
	SetButtonVisibility();
}

void USubMenuInventory::SetButtonVisibility()
{
	if (CurrentPage == MaxPage - 1)
		NextBtn->SetVisibility(ESlateVisibility::Hidden);
	else
		NextBtn->SetVisibility(ESlateVisibility::Visible);

	if (CurrentPage == 0)
		PrevBtn->SetVisibility(ESlateVisibility::Hidden);
	else
		PrevBtn->SetVisibility(ESlateVisibility::Visible);
}
