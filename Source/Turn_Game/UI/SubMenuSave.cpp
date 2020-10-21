// Fill out your copyright notice in the Description page of Project Settings.

#include "../GI_Archive.h"
#include "../GameSaver.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/PanelSlot.h"
#include "Blueprint/WidgetTree.h"
#include "SaveSlot.h"
#include "SubMenuSave.h"

void USubMenuSave::NativeConstruct()
{
	Super::NativeConstruct();
	UPanelWidget* RootWidget = Cast<UPanelWidget>(GetRootWidget());
	SaveSlotLayoutBox = WidgetTree->ConstructWidget<UVerticalBox>(UVerticalBox::StaticClass(), L"CharLayout");
	RootWidget->AddChild(SaveSlotLayoutBox);
}

void USubMenuSave::ConstructSubWidget()
{
	UGI_Archive* arch = Cast<UGI_Archive>(GetGameInstance());
	if (arch)
	{
		auto maxSlot = arch->GetMaxSaveSlot();
		for (int i = 0; i < maxSlot; i++)
		{
			if (SaveSlotWidgetClass)
			{
				USaveSlot* SaveSlot = Cast<USaveSlot>(CreateWidget<UUserWidget>(this, SaveSlotWidgetClass));
				if (SaveSlot)
				{
					SaveSlot->ConstructFromData(arch->GetSaveData(i), arch);
					SaveSlotLayoutBox->AddChildToVerticalBox(SaveSlot);
				}
			}
		}
	}
	// 박스안의 위젯들을 정렬하기 위해 구조체 생성.
	FSlateChildSize Size(ESlateSizeRule::Fill);
	Size.Value = 1.0f;
	auto SlotArr = SaveSlotLayoutBox->GetSlots();
	for (auto slot : SlotArr)
	{
		UVerticalBoxSlot* VertSlot = Cast<UVerticalBoxSlot>(slot);
		if (VertSlot)
		{
			VertSlot->SetSize(Size);
		}
	}
}
