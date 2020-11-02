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
		//UPanelSlot���� �޾ƿ� �� UVerticalBoxSlot���� �ٲ� SizeRule�� �ٲ��ش�
		//������ Weight�� ������ ���ĵ�
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
