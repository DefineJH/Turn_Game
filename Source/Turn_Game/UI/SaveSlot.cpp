// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveSlot.h"
#include "../GameSaver.h"
#include "../GI_Archive.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "PartyCharDisplay.h"

void USaveSlot::ConstructFromData(int idx, UGI_Archive* archive)
{
	UGameSaver* SaveData = archive->GetSaveData(idx);
	saveidx = idx;
	if (SaveData)
	{
		SaveInst = SaveData;
		MainChar->ConstructByData(SaveInst->GetCharInfo(SaveInst->MainChar), archive);
		SlotIndex->SetText(FText::FromString(SaveInst->SaveSlotName));
		PlayTime->SetText(FText::FromString(FString::FromInt(SaveInst->PlayTime_H) + L"H" + FString::FromInt(SaveInst->PlayTime_M) + L"M"));
	}
	else
	{
		ConstructInvalidData(archive);
	}

}

void USaveSlot::ConstructInvalidData(UGI_Archive* archive)
{
	Thumbnail->SetBrushFromTexture(archive->GetTextureFromName("Thumb_Empty"));
	MainChar->ConstructByData(archive->GetDefaultCharData(L"Louis"), archive);
	SlotIndex->SetText(FText::FromString(L"Slot" + FString::FromInt(saveidx)));
	PlayTime->SetText(FText::FromString(L"0H0M"));
}
