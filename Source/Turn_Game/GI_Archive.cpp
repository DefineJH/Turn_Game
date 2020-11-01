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

TOptional<USkeletalMesh*> UGI_Archive::QueryModel(FString name) 
{
	TOptional<USkeletalMesh*> optional;
	if (ModelArchive.Contains(name))
	{
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

FCharInfo UGI_Archive::GetCharInfo(FString CharName) const
{
	check(CurCharInfo.Contains(CharName));
	return CurCharInfo[CharName];
}

bool UGI_Archive::SetActiveChar(UPARAM(ref)FString & CharName)
{
	if (CurActiveChar.Num() == 3)
	{
		return false;
	}
	else
	{
		CurActiveChar.Add(CharName);
		CurCharInfo[CharName].bIsActive = true;
		return true;
	}
}

bool UGI_Archive::RemoveActiveChar(UPARAM(ref)FString& CharName)
{
	if (CurActiveChar.Num() == 0)
	{
		return false;
	}
	else
	{
		for (FString& name : CurActiveChar)
		{
			if (name.Equals(CharName))
			{
				CurActiveChar.Remove(CharName);
				CurCharInfo[CharName].bIsActive = false;
				return true;
			}
		}
		return false;
	}
}

bool UGI_Archive::IsActiveChar(UPARAM(ref)FString& CharName) const
{
	for (const FString& name : CurActiveChar)
	{
		if (name.Equals(CharName))
		{
			return true;
		}
	}
	return false;
}

void UGI_Archive::ChangeMainChar(UPARAM(ref)FString& CharName)
{
	MainChar = CharName;
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

	FString Last;

	StreamHandle.Get()->GetLoadedAssets(loaded);

	for (auto elem : loaded)
	{
		if (elem)
		{
			USkeletalMesh* mesh = Cast<USkeletalMesh>(elem);
			FString name = mesh->GetName();

			name.Split("_", nullptr, &Last);
			ModelArchive.Add(Last, mesh);
		}
	}

	StreamHandle.Get()->ReleaseHandle();

	if (MeshLoadDelegate.IsBound())
	{
		MeshLoadDelegate.Execute(Last);
		MeshLoadDelegate.Unbind();
	}
}


UTexture2D* UGI_Archive::GetTextureFromName(FString name) const
{
	if (TextureArchive.Contains(name))
		return TextureArchive[name];
	else
		return nullptr;
}

UPaperSprite* UGI_Archive::GetSpriteFromName(FString name) const
{
	if (UISpriteArchive.Contains(name))
	{

		return UISpriteArchive[name];
	}
	else
		return nullptr;
}

bool UGI_Archive::HasSaveData(int idx)
{
	if (UGameplayStatics::DoesSaveGameExist(L"Slot"+ FString::FromInt(idx), 0))
	{
		UE_LOG(LogTemp, Warning, L"Has Save Data");
		return true;
	}
	else
		return false;
}

void UGI_Archive::ConstructDefaultCharData()
{
	CurActiveChar = { "Mia" , "Louis", "Eva" };
	MainChar = "Louis";
	if (DefaultCharData_DT)
	{
		auto rownames = DefaultCharData_DT->GetRowNames();
		auto rowStruct = DefaultCharData_DT->GetRowStruct();
		for (auto& name : rownames)
		{
			FCharInfo* temp = DefaultCharData_DT->FindRow<FCharInfo>(name, "");
			if (temp)
			{
				for (auto& CharName : CurActiveChar)
				{
					if (temp->Name == CharName)
					{
						temp->bIsActive = true;
						break;
					}
					else
						temp->bIsActive = false;
				}
				CurCharInfo.Add(temp->Name, *temp);
			}
		}

	}
}

bool UGI_Archive::SaveCurrentData(int idx)
{
	UGameSaver* SaveInst = Cast<UGameSaver>(UGameplayStatics::CreateSaveGameObject(UGameSaver::StaticClass()));
	SaveInst->SaveSlotName = L"Slot" + FString::FromInt(idx);
	SaveInst->SaveIndex = 0;
	SaveInst->ActiveChar = CurActiveChar;
	UE_LOG(LogTemp, Warning, L"%s", *MainChar);
	SaveInst->MainChar = MainChar;
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

UGameSaver* UGI_Archive::GetSaveData(int idx)
{
	UGameSaver* SaveInst = nullptr;
	if (HasSaveData(idx))
	{
		SaveInst = Cast<UGameSaver>(UGameplayStatics::LoadGameFromSlot(L"Slot"+FString::FromInt(idx),0));
	}
	return SaveInst;
}

int8 UGI_Archive::GetMaxSaveSlot() const
{
	return MaxSaveSlot;
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



TOptional<FCharInfo> UGI_Archive::GetDefaultCharData(FString CharName) const
{
	TOptional<FCharInfo> info;
	if (DefaultCharData_DT)
	{
		auto rownames = DefaultCharData_DT->GetRowNames();
		auto rowStruct = DefaultCharData_DT->GetRowStruct();
		for (auto& name : rownames)
		{
			FCharInfo* temp = DefaultCharData_DT->FindRow<FCharInfo>(*CharName, "");
			if (temp)
			{
				info = *temp;
			}
		}
	}
	return info;
}
