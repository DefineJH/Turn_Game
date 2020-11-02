// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/UI/SubMenuParty.h"
#include "../Public/UI/PartyCharDisplay.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/PanelSlot.h"
#include "Components/SizeBox.h"
#include "Components/ScrollBoxSlot.h" 
#include "Components/Image.h"
#include "PaperSprite.h"
#include "PaperSpriteBlueprintLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "../Public/Custom/CustomStruct.h"
#include "../GI_Archive.h"


void USubMenuParty::ConstructSubWidget()
{
	if (!LayoutBox) return;
	LayoutBox->ClearChildren();

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
				USizeBox* SizeBox = WidgetTree->ConstructWidget<USizeBox>(USizeBox::StaticClass());

				FVector2D size = GEngine->GameViewport->Viewport->GetSizeXY();
				const float sizeY = size.Y / infos.Num();

				if (SizeBox)
				{
					SizeBox->AddChild(SingleChar);
					SizeBox->SetMinDesiredHeight(sizeY * 1.5f);
					SizeBox->SetMinDesiredWidth(size.X);

					LayoutBox->AddChild(SizeBox);
				}
			}
		}
		//UPanelSlot으로 받아온 후 UVerticalBoxSlot으로 바꿔 SizeRule을 바꿔준다
		//동일한 Weight를 가지고 정렬됨
		auto SlotArr = LayoutBox->GetSlots();
		for (auto slot : SlotArr)
		{
			UScrollBoxSlot* ScrollSlot = Cast<UScrollBoxSlot>(slot);
			if (ScrollSlot)
			{
				ScrollSlot->SetHorizontalAlignment(HAlign_Fill);
				ScrollSlot->SetVerticalAlignment(VAlign_Fill);
			}
		}
	}
}

void USubMenuParty::UpdateSubWidget()
{
	ConstructSubWidget();
}
