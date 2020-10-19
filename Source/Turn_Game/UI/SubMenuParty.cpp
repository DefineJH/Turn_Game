// Fill out your copyright notice in the Description page of Project Settings.


#include "SubMenuParty.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "Components/PanelSlot.h"
#include "Components/VerticalBoxSlot.h" 
#include "Components/Image.h"
#include "PaperSprite.h"
#include "Blueprint/WidgetTree.h"
#include "../Custom/CustomStruct.h"
#include "../GI_Archive.h"

void USubMenuParty::NativeConstruct()
{
	Super::NativeConstruct();
	UPanelWidget* RootWidget = Cast<UPanelWidget>(GetRootWidget());
	CharLayoutBox = WidgetTree->ConstructWidget<UVerticalBox>(UVerticalBox::StaticClass(), L"CharLayout");
	RootWidget->AddChild(CharLayoutBox);
}

void USubMenuParty::ConstructSubWidget()
{
	if (!CharLayoutBox) return;

	UGI_Archive* Archive = Cast<UGI_Archive>(GetGameInstance());

	if (Archive)
	{
		auto infos = Archive->GetCharInfo();
		// �ڽ����� �������� �����ϱ� ���� ����ü ����.
		FSlateChildSize Size(ESlateSizeRule::Fill);
		Size.Value = 1.0f;
		// ĳ���� ���� ������ ���� ������ ���� ����
		for (auto info : infos)
		{
			UUserWidget* SingleChar = CreateWidget<UUserWidget>(this, CharDisplayWidget);
			if (SingleChar)
			{
				UPaperSprite* sprite = Archive->GetSpriteFromName(Archive->GetFStringFromEnum("EElementType", (int32)info.type));
				UTexture2D* tex = Archive->GetTextureFromName(info.Name);
				if (tex)
				{
					Cast<UImage>(SingleChar->GetWidgetFromName(L"CharImage"))->SetBrushFromTexture(tex);
				}
				FString str = Archive->GetFStringFromEnum("EElementalType", (int32)info.type);
				UE_LOG(LogTemp, Warning, L"%s", *str);
				if (sprite)
				{
					UImage* tempImg = Cast<UImage>(SingleChar->GetWidgetFromName(L"Elemental"));
					tempImg->SetBrushFromAtlasInterface(sprite->GetSlateAtlasData());
				}
				//�׳� �̸��� �ٲ���
				Cast<UTextBlock>(SingleChar->GetWidgetFromName(L"Name"))->SetText(FText::FromString(*info.Name));
				Cast<UTextBlock>(SingleChar->GetWidgetFromName(L"Level"))->SetText(FText::FromString(*FString::FromInt(info.iLevel)));
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
