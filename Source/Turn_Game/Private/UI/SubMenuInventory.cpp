// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/UI/SubMenuInventory.h"
#include "../Public/UI/InvenView.h"
#include "../Public/Custom/CusomEnum.h"

void USubMenuInventory::ConstructSubWidget()
{
	uint8 categoryNum = (uint8)EItemType::EIT_MAX;

	CategoryWidgets.Reserve(categoryNum);

	for (int i = 0; i < categoryNum; i++)
	{
		UInvenView* singleInven = CreateWidget<UInvenView>(this, UInvenView::StaticClass());
		if (singleInven)
		{
			CategoryWidgets.Add(singleInven);
		}
	}
}

void USubMenuInventory::UpdateSubWidget()
{

}
