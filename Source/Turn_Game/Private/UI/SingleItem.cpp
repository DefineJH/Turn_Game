// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/UI/SingleItem.h"
#include "../Public/Custom/CustomStruct.h"
#include "../Public/ItemDataObject.h"
#include "../GI_Archive.h"
#include "ItemDataObject.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void USingleItem::NativeOnListItemObjectSet(UObject* ItemObj)
{
	itemData = Cast<UItemDataObject>(ItemObj);
	if (itemData)
	{
		const FItemInformation info = itemData->GetInfo();

		UGI_Archive* arch = Cast<UGI_Archive>(GetGameInstance());
		if (arch)
		{
			UE_LOG(LogTemp, Warning, L"%d", arch->GetItemQuantity(info.ItemCode));

			ItemQuantity->SetText(FText::FromString(FString::FromInt(arch->GetItemQuantity(info.ItemCode))));
			ItemImage->SetBrushFromTexture(arch->GetTextureFromName(FString::FromInt(info.ItemCode)));
			ItemName->SetText(FText::FromString(info.ItemName));
			ItemDesc->SetText(FText::FromString(info.ItemDesc));
		}
	}
}

void USingleItem::NativeOnItemSelectionChanged_Implementation(bool bIsSelected)
{

}

