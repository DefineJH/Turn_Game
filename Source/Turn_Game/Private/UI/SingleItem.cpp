// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/UI/SingleItem.h"
#include "../Public/Custom/CustomStruct.h"
#include "../Public/ItemDataObject.h"
#include "../GI_Archive.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"



void USingleItem::NativeOnListItemObjectSet(UObject * ItemObj)
{
	UItemDataObject* item = Cast<UItemDataObject>(ItemObj);
	if (item)
	{
		const FItemInformation info = item->GetInfo();

		UGI_Archive* arch = Cast<UGI_Archive>(GetGameInstance());
		if (arch)
		{
			ItemQuantity->SetText(FText::FromString(FString::FromInt(arch->GetItemQuantity(info.ItemCode))));
			ItemImage->SetBrushFromTexture(arch->GetTextureFromName(FString::FromInt(info.ItemCode)));
			ItemName->SetText(FText::FromString(info.ItemName));
		}
	}
}

void USingleItem::NativeOnItemSelectionChanged(bool bIsSelected)
{

}
