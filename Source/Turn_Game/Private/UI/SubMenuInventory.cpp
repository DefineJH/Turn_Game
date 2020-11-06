// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/UI/SubMenuInventory.h"
#include "../Public/UI/InvenView.h"
#include "../Public/Custom/CusomEnum.h"

void USubMenuInventory::ConstructSubWidget()
{
	CurrentPage = 0;
	MaxPage = (uint8)EItemType::EIT_MAX;

	for (uint8 i = 0; i < MaxPage; i++)
	{
		UInvenView* singleInven = CreateWidget<UInvenView>(this, UInvenView::StaticClass());

		singleInven->ConstructInven((EItemType)i);
		if (singleInven)
		{
			CategoryWidgets.Add(singleInven);
		}
	}
}

void USubMenuInventory::UpdateSubWidget()
{

}

void USubMenuInventory::ShowPage(uint8 page)
{

}
