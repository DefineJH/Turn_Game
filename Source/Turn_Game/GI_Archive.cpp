// Fill out your copyright notice in the Description page of Project Settings.


#include "GI_Archive.h"
#include "GameSaver.h"
#include "Custom/CustomStruct.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/Optional.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Engine/Texture2D.h"
#include "PaperSprite.h"
#include "Engine/DataTable.h"
#include "Turn_GameGameModeBase.h"

void UGI_Archive::LoadModels(TArray<FString> CharName)
{
	bIsLoadCompleted = false;
	auto& assetLoader = UAssetManager::GetStreamableManager();
	TArray<FSoftObjectPath> toStream;
	for (auto& name : CharName)
	{
		if (!ModelArchive.Contains(name))
		{
			toStream.AddUnique(PathArchive[name]);
		}
	}
	StreamHandle = assetLoader.RequestAsyncLoad(toStream, FStreamableDelegate::CreateUObject(this, &UGI_Archive::OnMeshLoadCompleted));
}

//TOptional<TSharedPtr<USkeletalMesh>> UGI_Archive::QueryModel(FString name)
TOptional<USkeletalMesh*> UGI_Archive::QueryModel(FString name)
{
	TOptional<USkeletalMesh*> optional;
	UE_LOG(LogTemp, Warning, L"Find %s Called", *name);
	if (ModelArchive.Contains(name))
	{
		UE_LOG(LogTemp, Warning, L"Model Returned");
		optional = ModelArchive[name];
	}
	else
	{
		LoadModels({ name });
	}
	return optional;
}

TArray<FCharInfo> UGI_Archive::GetCharInfo() const
{
	TArray<FCharInfo> tempInfo;
	tempInfo.Reserve(8);

	for (auto& tmp : CurCharInfo)
	{
		if (tmp.Value.bIsInParty)
			tempInfo.Add(tmp.Value);
	}
	return tempInfo;
}

void UGI_Archive::ConstructModelPath()
{
	if (ModelPath_DT)
	{
		auto rownames = ModelPath_DT->GetRowNames();
		auto rowStruct = ModelPath_DT->GetRowStruct();
		for (auto& name : rownames)
		{
			FModelPath* temp = ModelPath_DT->FindRow<FModelPath>(name, "");
			if (temp)
			{
				PathArchive.Add(temp->Name, temp->Path);
			}
		}

	}
}

void UGI_Archive::Init()
{
	Super::Init();
	ConstructModelPath();
	ConstructDefaultCharData();

	LoadModels(CurActiveChar);

	FTimerHandle WaitHandle;
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
	{
		ATurn_GameGameModeBase* GameMode = Cast<ATurn_GameGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
		}
	}), 1.0f, false);

}


void UGI_Archive::OnMeshLoadCompleted()
{
	bIsLoadCompleted = true;

	TArray<UObject*> loaded;
	StreamHandle.Get()->GetLoadedAssets(loaded);

	for (auto elem : loaded)
	{
		if (elem)
		{
			USkeletalMesh* mesh = Cast<USkeletalMesh>(elem);
			FString name = mesh->GetName();
			FString Last;

			name.Split("_", nullptr, &Last);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *Last);
			//ModelArchive.Add(Last, MakeShareable(mesh));
			ModelArchive.Add(Last, mesh);
		}
	}

	StreamHandle.Get()->ReleaseHandle();
}


UTexture2D* UGI_Archive::GetTextureFromName(FString name) const
{
	if (UICharImgArchive.Contains(name))
		return UICharImgArchive[name];
	else
		return nullptr;
}

UPaperSprite* UGI_Archive::GetSpriteFromName(FString name) const
{
	UE_LOG(LogTemp, Warning, L"%s sprite Called", *name);
	if (UISpriteArchive.Contains(name))
	{

		return UISpriteArchive[name];
	}
	else
		return nullptr;
}

bool UGI_Archive::HasSaveData(int idx)
{
	if (UGameplayStatics::DoesSaveGameExist(L"Default", idx))
		return true;
	else
		return false;
}

void UGI_Archive::ConstructDefaultCharData()
{
	CurActiveChar = { "Mia" , "Louis", "Eva" };
	if (DefaultCharData_DT)
	{
		auto rownames = DefaultCharData_DT->GetRowNames();
		auto rowStruct = DefaultCharData_DT->GetRowStruct();
		for (auto& name : rownames)
		{
			FCharInfo* temp = DefaultCharData_DT->FindRow<FCharInfo>(name, "");
			if (temp)
			{
				CurCharInfo.Add(temp->Name, *temp);
			}
		}

	}
}

bool UGI_Archive::SaveCurrentData(int idx)
{
	UGameSaver* SaveInst = Cast<UGameSaver>(UGameplayStatics::CreateSaveGameObject(UGameSaver::StaticClass()));
	SaveInst->SaveSlotName = L"Default";
	SaveInst->SaveIndex = idx;

	SaveInst->ActiveChar = CurActiveChar;
	for (auto& tmp : CurCharInfo)
	{
		SaveInst->CharInfos.Add(tmp.Value);
	}
	if (UGameplayStatics::SaveGameToSlot(SaveInst, SaveInst->SaveSlotName, SaveInst->SaveIndex))
	{
		return true;
	}
	else
		return false;
}

FString UGI_Archive::GetFStringFromEnum(FString StrEnumClass, int32 Value)
{
	const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, *StrEnumClass, true);
	if (!enumPtr)
		return "Invalid";
	else
	{
		FString temp = enumPtr->GetNameStringByValue(Value);
		FString last;
		temp.Split("_", nullptr, &last);
		return last;
	}
}