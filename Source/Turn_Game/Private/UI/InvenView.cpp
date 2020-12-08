// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/UI/InvenView.h"
#include "../Public/Custom/CustomStruct.h"
#include "../Public/ItemDataObject.h"
#include "../GI_Archive.h"
#include "../Public/UI/PartyCharDisplay.h"
#include "../Public/UI/SingleItem.h"
#include "Components/ListView.h"
#include "Components/ScrollBox.h"
#include "Components/WidgetSwitcher.h"
#include "Components/WidgetSwitcherSlot.h"
#include "Components/TextBlock.h"
#include "Components/SizeBox.h"
#include "Components/Button.h"
#include "Components/ScrollBoxSlot.h"
#include "Blueprint/WidgetTree.h"

void UInvenView::ConstructList(EItemType CategoryType)
{
	LeftSwitch = false;
	invenType = CategoryType;
	UGI_Archive* arch = Cast<UGI_Archive>(GetGameInstance());
	if (arch)
	{
		TArray<FItemInformation> items = arch->GetCurItemInfoByCategory(CategoryType);
		for (auto& info : items)
		{
			UItemDataObject* dataObj = NewObject<UItemDataObject>(this);
			dataObj->SetInfo(info);
			if(ItemListView && arch->GetItemQuantity(info.ItemCode) > 0)
				ItemListView->AddItem(dataObj);
		}
	}

}

void UInvenView::SelectItem(UItemDataObject* SelectedItem)
{
	SelectedItemData = SelectedItem;
	SelectedItemWidget = ItemListView->GetEntryWidgetFromItem<USingleItem>(SelectedItem);
}

void UInvenView::SetFocus()
{
	ItemListView->SetKeyboardFocus();
}

void UInvenView::UseCurSelectedItem(FString TargetChar)
{
	UGI_Archive* arch = Cast<UGI_Archive>(GetGameInstance());
	if (arch)
	{
		int32 itemcode = -1;
		if (SelectedItemWidget)
		{
			itemcode = SelectedItemData->GetInfo().ItemCode;
			if (arch->UseItem(itemcode, TargetChar))
			{
				UE_LOG(LogTemp, Warning, L"ItemUsed");
			}
			else
			{
				UE_LOG(LogTemp, Warning, L"ItemCantUsed");

			}
		}
		ItemListView->ClearListItems();
		ConstructList(invenType);
	}
}
