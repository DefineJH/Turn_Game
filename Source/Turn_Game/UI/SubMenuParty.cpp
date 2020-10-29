// Fill out your copyright notice in the Description page of Project Settings.


#include "SubMenuParty.h"
#include "PartyCharDisplay.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "Components/PanelSlot.h"
#include "Components/VerticalBoxSlot.h" 
#include "Components/Image.h"
#include "PaperSprite.h"
#include "PaperSpriteBlueprintLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "../Custom/CustomStruct.h"
#include "../GI_Archive.h"

void USubMenuParty::NativeConstruct()
{
	Super::NativeConstruct();
	//UPanelWidget* RootWidget = Cast<UPanelWidget>(GetRootWidget());
	//CharLayoutBox = WidgetTree->ConstructWidget<UVerticalBox>(UVerticalBox::StaticClass(),   L"CharLayout");
	//RootWidget->AddChild(CharLayoutBox);
}

void USubMenuParty::ConstructSubWidget()
{
	if (!CharLayoutBox) return;
	CharLayoutBox->ClearChildren();

	UGI_Archive* Archive = Cast<UGI_Archive>(GetGameInstance());

	if (Archive)
	{
		TArray<FCharInfo> infos = Archive->GetCharInfo();
		// �ڽ����� �������� �����ϱ� ���� ����ü ����.
		FSlateChildSize Size(ESlateSizeRule::Fill);
		Size.Value = 1.0f;
		// ĳ���� ���� ������ ���� ������ ���� ����
		for (FCharInfo& info : infos)
		{
			UPartyCharDisplay* SingleChar = Cast<UPartyCharDisplay>(CreateWidget<UUserWidget>(this, CharDisplayWidget));
			if (SingleChar)
			{
				SingleChar->ConstructByData(info,Archive);
				CharLayoutBox->AddChildToVerticalBox(SingleChar);
			}
		}
		//UPanelSlot���� �޾ƿ� �� UVerticalBoxSlot���� �ٲ� SizeRule�� �ٲ��ش�
		//������ Weight�� ������ ���ĵ�
		auto SlotArr = CharLayoutBox->GetSlots();
		for (auto slot : SlotArr)
		{
			UVerticalBoxSlot* VertSlot = Cast<UVerticalBoxSlot>(slot);
			if (VertSlot)
			{
				VertSlot->SetSize(Size);
			}
		}
	}
}

void USubMenuParty::UpdateSubWidget()
{
	ConstructSubWidget();
}
