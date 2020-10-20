// Fill out your copyright notice in the Description page of Project Settings.

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

}
