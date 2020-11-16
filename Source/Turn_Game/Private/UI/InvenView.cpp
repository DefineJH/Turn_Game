// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/UI/InvenView.h"
#include "../Public/Custom/CustomStruct.h"
#include "../Public/ItemDataObject.h"
#include "../GI_Archive.h"
#include "../Public/UI/PartyCharDisplay.h"
#include "Components/ListView.h"
#include "Components/ScrollBox.h"
#include "Components/WidgetSwitcher.h"
#include "Components/WidgetSwitcherSlot.h"
#include "Components/TextBlock.h"
#include "Components/SizeBox.h"
#include "Components/Button.h"
void UInvenView::ConstructList(EItemType CategoryType)
{
	LeftSwitch = false;
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
	}
	if (CategoryType == EItemType::EIT_Use || CategoryType == EItemType::EIT_Skill)
	{
		if (arch)
		{
			auto charArr = arch->GetPartyCharsInfo();
			if (MiniChar)
			{
				for (FCharInfo& info : charArr)
				{
					UPartyCharDisplay* display = Cast<UPartyCharDisplay>(CreateWidget<UUserWidget>(this, MiniChar));
					if (display)
					{
						UE_LOG(LogTemp, Warning, L"Here");
						display->ConstructByData(info, arch);
						UButton* CharBtn = Cast<UButton>(display->GetWidgetFromName("Button_42"));
						CharBtn->OnClicked.RemoveAll(CharBtn);

						FSlateChildSize Size(ESlateSizeRule::Fill);
						Size.Value = 1.0f;

						UPartyCharDisplay* SingleChar = Cast<UPartyCharDisplay>(CreateWidget<UUserWidget>(this, CharDisplayWidget));
						if (SingleChar)
						{
							SingleChar->ConstructByData(info, arch);
							USizeBox* SizeBox = WidgetTree->ConstructWidget<USizeBox>(USizeBox::StaticClass());

							FVector2D size = GEngine->GameViewport->Viewport->GetSizeXY();
							const float sizeY = size.Y / charArr.Num();

							if (SizeBox)
							{
								SizeBox->AddChild(SingleChar);
								SizeBox->SetMinDesiredHeight(sizeY * 1.5f);

								CharBox->AddChild(SizeBox);
							}
						}
					}
				}
			}
		}
	}
}

void UInvenView::ToggleUse()
{
	LeftSwitch = !LeftSwitch;
	LeftSwitcher->SetActiveWidgetIndex(LeftSwitch);
}

void UInvenView::SelectItem(UItemDataObject* SelectedItem)
{
	ItemData = SelectedItem->GetInfo();
}
