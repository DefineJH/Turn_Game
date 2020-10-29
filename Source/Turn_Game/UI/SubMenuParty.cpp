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
		// 박스안의 위젯들을 정렬하기 위해 구조체 생성.
		FSlateChildSize Size(ESlateSizeRule::Fill);
		Size.Value = 1.0f;
		// 캐릭터 설명 위젯을 받은 정보를 토대로 만듦
		for (FCharInfo& info : infos)
		{
			UPartyCharDisplay* SingleChar = Cast<UPartyCharDisplay>(CreateWidget<UUserWidget>(this, CharDisplayWidget));
			if (SingleChar)
			{
				SingleChar->ConstructByData(info,Archive);
				CharLayoutBox->AddChildToVerticalBox(SingleChar);
			}
		}
		//UPanelSlot으로 받아온 후 UVerticalBoxSlot으로 바꿔 SizeRule을 바꿔준다
		//동일한 Weight를 가지고 정렬됨
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
