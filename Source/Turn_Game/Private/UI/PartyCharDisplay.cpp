// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/UI/PartyCharDisplay.h"
#include "../Public/Custom/CustomStruct.h"
#include "../GI_Archive.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "PaperSprite.h"

void UPartyCharDisplay::ConstructByData(FCharInfo info, UGI_Archive* archive)
{
	UPaperSprite* sprite = archive->GetSpriteFromName(archive->GetFStringFromEnum("EElementalType", (int32)info.type));
	UTexture2D* tex = archive->GetTextureFromName(info.Name);
	if (tex)
	{
		Image_Char->SetBrushFromTexture(tex);
	}
	if (sprite)
	{
		UImage* tempImg = Cast<UImage>(Elemental);
		tempImg->SetBrushFromAtlasInterface(sprite, true);
	}
	tex = nullptr;
	tex = archive->GetTextureFromName(info.bIsActive ? "Check" : "NonCheck");
	if (tex)
	{
		Image_Select->SetBrushFromTexture(tex);
	}
	//±◊≥… ¿Ã∏ß∏∏ πŸ≤„¡‹
	Cast<UTextBlock>(Name)->SetText(FText::FromString(*info.Name));
	Cast<UTextBlock>(Level)->SetText(FText::FromString(*FString::FromInt(info.iLevel)));

	Text_HP->SetText(FText::FromString(FString::FromInt(info.iMaxHP) + L"//" + FString::FromInt(info.iHP)));
	Text_SP->SetText(FText::FromString(FString::FromInt(info.iMaxSP) + L"//" + FString::FromInt(info.iSP)));
	Text_EXP->SetText(FText::FromString(FString::FromInt(info.iExp) + L"//" + FString::FromInt(100)));

	Progress_HP->SetPercent(info.iHP / info.iMaxHP);
	Progress_SP->SetPercent(info.iSP / info.iMaxSP);
	Progress_EXP->SetPercent(info.iSP / 100);
}

void UPartyCharDisplay::ConstructByData(TOptional<FCharInfo> info, UGI_Archive* archive)
{
	if (info.IsSet())
	{
		ConstructByData(*info, archive);
	}
}
