// Fill out your copyright notice in the Description page of Project Settings.


#include "SubMenuParty.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "Components/PanelSlot.h"
#include "Components/VerticalBoxSlot.h"
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
				//�׳� �̸��� �ٲ���
				Cast<UTextBlock>(SingleChar->GetWidgetFromName(L"Name"))->SetText(FText::FromString(*info.Name));
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
