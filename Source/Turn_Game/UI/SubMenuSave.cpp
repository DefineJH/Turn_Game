// Fill out your copyright notice in the Description page of Project Settings.

#include "GI_Archvie.h"
#include "Components/VerticalBox.h"
#include "Blueprint/WidgetTree.h"
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
	UGI_Archvie* arch = Cast<UGI_Archvie>(GetGameInstance());
	if (arch)
	{
		auto maxSlot = arch->GetMaxSaveSlot();
		for (int i = 0; i < maxSlot; i++)
		{
		}
	}
}
