// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveSlot.h"
#include "../GameSaver.h"
#include "../GI_Archive.h"
#include "Components/TextBlock.h"
#include "PartyCharDisplay.h"

void USaveSlot::ConstructFromData(UGameSaver* SaveData, UGI_Archive* archive)
{
	if (SaveData)
	{
		SaveInst = SaveData;
		MainChar->ConstructByData(SaveData->GetCharInfo(archive->GetMainChar()), archive);
		SlotIndex->SetText(FText::FromString(FString::FromInt(SaveInst->SaveIndex)));
		PlayTime->SetText(FText::FromString(FString::FromInt(SaveInst->PlayTime_H) + L"H" + FString::FromInt(SaveInst->PlayTime_M) + L"M"));
	}
	else
	{
		ConstructInvalidData(archive);
	}

}

void USaveSlot::ConstructInvalidData(UGI_Archive* archive)
{
	MainChar->ConstructByData(archive->GetDefaultCharData(archive->GetMainChar()), archive);
	SlotIndex->SetText(FText::FromString(L"None"));
	PlayTime->SetText(FText::FromString(L"0H0M"));
}
