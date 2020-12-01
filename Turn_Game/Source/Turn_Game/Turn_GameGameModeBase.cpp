// Copyright Epic Games, Inc. All Rights Reserved.


#include "Turn_GameGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameSaver.h"
#include "GI_Archive.h"



void ATurn_GameGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void ATurn_GameGameModeBase::Save(int idx)
{
	UGameSaver* SaveInst = Cast<UGameSaver>(UGameplayStatics::CreateSaveGameObject(UGameSaver::StaticClass()));

}

void ATurn_GameGameModeBase::Load(int idx)
{
	UGameSaver* LoadGameInstance = Cast<UGameSaver>(UGameplayStatics::CreateSaveGameObject(UGameSaver::StaticClass()));

	if (LoadGameInstance)
	{
		LoadGameInstance->SaveSlotName = "MySaveGame";
		LoadGameInstance->SaveIndex = idx;
		LoadGameInstance = Cast<UGameSaver>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->SaveIndex));
		if (LoadGameInstance)
		{
			LoadGameInstance->ActiveChar = ActiveChar;
		}
		else
		{
			SetDefaultData();
		}
	}
}

void ATurn_GameGameModeBase::SetDefaultData()
{
	
	ActiveChar = { "Mia","Louis","Eva" };
}

const TArray<FString> * const ATurn_GameGameModeBase::GetActiveChar() const
{
	return &ActiveChar;
}

USkeletalMesh* ATurn_GameGameModeBase::GetCharMesh(FString CharName) const
{
	UGI_Archive* GameInst = Cast<UGI_Archive>(GetGameInstance());
	if (GameInst)
	{
		auto Mesh = GameInst->QueryModel(CharName);
		return Mesh.Get(nullptr);
	}
	return nullptr;
}

