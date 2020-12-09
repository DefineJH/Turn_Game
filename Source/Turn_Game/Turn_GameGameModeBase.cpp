// Copyright Epic Games, Inc. All Rights Reserved.


#include "Turn_GameGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "ExplorerChar.h"
#include "GameSaver.h"
#include "GI_Archive.h"



void ATurn_GameGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}


void ATurn_GameGameModeBase::Save(int idx)
{
	UGI_Archive* arch = Cast<UGI_Archive>(GetGameInstance());
	if (arch)
	{
		arch->SaveCurrentData(idx);
	}
}

void ATurn_GameGameModeBase::Load(int idx)
{
	UGameSaver* LoadGameInstance = Cast<UGameSaver>(UGameplayStatics::CreateSaveGameObject(UGameSaver::StaticClass()));

	if (LoadGameInstance)
	{
		LoadGameInstance->SaveSlotName = L"Slot" + FString::FromInt(idx);
		LoadGameInstance->SaveIndex = 0;
		LoadGameInstance = Cast<UGameSaver>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->SaveIndex));
		if (LoadGameInstance)
		{
			UGI_Archive* arch = Cast<UGI_Archive>(GetGameInstance());
			if (arch)
			{
				arch->LoadGameFromData(LoadGameInstance);
			}
		}
	}
}

USkeletalMesh* ATurn_GameGameModeBase::GetCharMesh(FString CharName , AExplorerChar* ToSet) 
{

	UGI_Archive* GameInst = Cast<UGI_Archive>(GetGameInstance());
	if (GameInst)
	{
		bool MeshSet = GameInst->LoadModels({ CharName });
		if (MeshSet)
			return GameInst->QueryModel(CharName).GetValue();
		else
		{
			MeshLoadChar = ToSet;
			GameInst->MeshLoadDelegate.BindUFunction(this, L"SetCharMesh");
			return nullptr;
		}
	}
	return nullptr;
}

void ATurn_GameGameModeBase::SetCharMesh(const TArray<FString>& CharName)
{
	UGI_Archive* GameInst = Cast<UGI_Archive>(GetGameInstance());
	if (GameInst)
	{
		auto mesh = GameInst->QueryModel(CharName[0]);
		if(MeshLoadChar && mesh.IsSet())
			MeshLoadChar->GetMesh()->SetSkeletalMesh(mesh.GetValue());
	}
}
