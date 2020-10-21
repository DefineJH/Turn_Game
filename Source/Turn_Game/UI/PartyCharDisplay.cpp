// Fill out your copyright notice in the Description page of Project Settings.


#include "PartyCharDisplay.h"
#include "../Custom/CustomStruct.h"
#include "../GI_Archive.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "PaperSprite.h"

void UPartyCharDisplay::ConstructByData(FCharInfo info, UGI_Archive* archive)
{
	UPaperSprite* sprite = archive->GetSpriteFromName(archive->GetFStringFromEnum("EElementalType", (int32)info.type));
	UTexture2D* tex = archive->GetTextureFromName(info.Name);
	if (tex)
	{
		CharImage->SetBrushFromTexture(tex);
	}
	if (sprite)
	{
		UE_LOG(LogTemp, Warning, L"Load Success");
		UImage* tempImg = Cast<UImage>(Elemental);
		tempImg->SetBrushFromAtlasInterface(sprite, true);
	}
	//±◊≥… ¿Ã∏ß∏∏ πŸ≤„¡‹
	Cast<UTextBlock>(Name)->SetText(FText::FromString(*info.Name));
	Cast<UTextBlock>(Level)->SetText(FText::FromString(*FString::FromInt(info.iLevel)));
}

void UPartyCharDisplay::ConstructByData(TOptional<FCharInfo> info, UGI_Archive* archive)
{
	if (info.IsSet())
	{
		ConstructByData(*info, archive);
	}
}
