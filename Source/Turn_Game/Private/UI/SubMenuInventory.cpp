// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/UI/SubMenuInventory.h"
#include "../Public/UI/InvenView.h"
#include "../Public/Custom/CusomEnum.h"
#include "Components/WidgetSwitcher.h"

void USubMenuInventory::ConstructSubWidget()
{
	CurrentPage = 0;
	MaxPage = (uint8)EItemType::EIT_MAX;

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
	ShowPage(0);
}

void USubMenuInventory::UpdateSubWidget()
{

}

void USubMenuInventory::ShowPage(uint8 page)
{
	Switcher->SetActiveWidgetIndex(page);
	UE_LOG(LogTemp, Warning, L"Show InvenView0");
}
