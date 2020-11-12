// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/UI/InvenView.h"
#include "../Public/Custom/CustomStruct.h"
#include "../Public/ItemDataObject.h"
#include "../GI_Archive.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"

void UInvenView::ConstructList(EItemType CategoryType)
{
	UGI_Archive* arch = Cast<UGI_Archive>(GetGameInstance());
	if (arch)
	{
		TArray<FItemInformation> items = arch->GetCurItemInfoByCategory(CategoryType);
		for (auto& info : items)
		{
			UItemDataObject* dataObj = NewObject<UItemDataObject>(this);
			dataObj->SetInfo(info);
			UE_LOG(LogTemp, Warning, L"item Added %s", *info.ItemName);
			if(ItemListView)
				ItemListView->AddItem(dataObj);
			else
				UE_LOG(LogTemp, Warning, L"list didnt created");
		}
		Text_Category->SetText(FText::FromString(arch->GetFStringFromEnum("EItemType", (int32)CategoryType)));
	}
}