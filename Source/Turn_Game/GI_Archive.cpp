// Fill out your copyright notice in the Description page of Project Settings.


#include "GI_Archive.h"
#include "Custom/CustomStruct.h"
#include "Misc/Optional.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
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
	StreamHandle = assetLoader.RequestAsyncLoad(toStream, FStreamableDelegate::CreateUObject(this, &UGI_Archive::OnLoadCompleted));
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

	FTimerHandle WaitHandle;
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]()
	{
		ATurn_GameGameModeBase* GameMode = Cast<ATurn_GameGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			LoadModels(*GameMode->GetActiveChar());
		}
	}), 1.0f, false);

	
}


void UGI_Archive::OnLoadCompleted()
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

