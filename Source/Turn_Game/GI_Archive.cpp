// Fill out your copyright notice in the Description page of Project Settings.


#include "GI_Archive.h"
#include "GameSaver.h"
#include "Public/Custom/CustomStruct.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/Optional.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Engine/Texture2D.h"
#include "PaperSprite.h"
#include "Engine/DataTable.h"
#include "Turn_GameGameModeBase.h"
#include "Containers/Map.h"
bool UGI_Archive::LoadModels(TArray<FString> CharName)
{
	bIsLoadCompleted = false;
	LoadChars = CharName;
	auto& assetLoader = UAssetManager::GetStreamableManager();
	TArray<FSoftObjectPath> toStream;
	for (auto& name : CharName)
	{
		if (!ModelArchive.Contains(name))
		{
			toStream.AddUnique(PathArchive[name]);
		}
		
	}
	if (toStream.Num() == 0)
	{
		return true;
	}
	else
	{
		StreamHandle = assetLoader.RequestAsyncLoad(toStream, FStreamableDelegate::CreateUObject(this, &UGI_Archive::OnMeshLoadCompleted));
		return false;
	}
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
		MeshLoadDelegate.Execute(LoadChars);
		MeshLoadDelegate.Unbind();
	}
}
TArray<FCharInfo> UGI_Archive::GetPartyCharsInfo() const
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

TArray<FCharInfo> UGI_Archive::GetActiveCharsInfo() const
{
	TArray<FCharInfo> tempInfo;
	tempInfo.Reserve(5);

	for (auto& tmp : CurCharInfo)
	{
		if (tmp.Value.bIsActive)
			tempInfo.Add(tmp.Value);
	}
	return tempInfo;
}

const FCharInfo& UGI_Archive::GetCharInfo(FString CharName) const
{
	check(CurCharInfo.Contains(CharName));
	return CurCharInfo[CharName];
}

bool UGI_Archive::SetCharInfo(FCharInfo CharInfo)
{
	FCharInfo* info = CurCharInfo.Find(CharInfo.Name);
	if (info)
	{
		*info = CharInfo;
		return true;
	}
	return false;
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

const FItemInformation& UGI_Archive::GetItemInfo(int32 itemCode) const
{
	return *ItemInfos.FindByPredicate([itemCode](const FItemInformation& info) { return info.ItemCode == itemCode; });
}

int8 UGI_Archive::GetItemQuantity(int32 itemCode) const
{
	if (CurItems.Contains(itemCode))
	{
		return CurItems[itemCode];
	}
	return 0;
}

TArray<FItemInformation> UGI_Archive::GetItemInfoByCategory(EItemType type)
{
	return ItemInfos.FilterByPredicate([type](const FItemInformation& info) { return info.type == type; });
}

TArray<FItemInformation> UGI_Archive::GetCurItemInfoByCategory(EItemType type)
{
	TArray<FItemInformation> itemarr;
	for (auto& item : CurItems)
	{
		FItemInformation tempinfo = GetItemInfo(item.Key);
		if (tempinfo.type == type)
		{
			itemarr.Add(FItemInformation(tempinfo));
		}
	}
	return itemarr;
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

void UGI_Archive::ConstructItemInfo()
{
	if (ItemData_DT)
	{
		auto rownames = ItemData_DT->GetRowNames();
		auto rowStruct = ItemData_DT->GetRowStruct();
		for (auto& name : rownames)
		{
			FItemInformation* temp = ItemData_DT->FindRow<FItemInformation>(name, "");
			if (temp)
			{
				ItemInfos.Add(*temp);
			}
		}
	}
	ItemInfos.Sort([](const FItemInformation& lhs, const FItemInformation& rhs)
	{
		return lhs.ItemCode < rhs.ItemCode;
	});

}

void UGI_Archive::Init()
{
	Super::Init();
	ConstructModelPath();
	ConstructItemInfo();

	ConstructDefaultData();
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

void UGI_Archive::ConstructDefaultData()
{
	CurActiveChar = { "Mia" , "Louis", "Eva" };
	MainChar = "Louis";

	CurItems.Emplace(0, 2);
	CurItems.Emplace(1, 2);
}

bool UGI_Archive::SaveCurrentData(int idx)
{
	UGameSaver* SaveInst = Cast<UGameSaver>(UGameplayStatics::CreateSaveGameObject(UGameSaver::StaticClass()));
	SaveInst->SaveSlotName = L"Slot" + FString::FromInt(idx);
	SaveInst->SaveIndex = 0;
	SaveInst->ActiveChar = CurActiveChar;
	SaveInst->MainChar = MainChar;
	SaveInst->Items = CurItems;
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



bool UGI_Archive::UseItem(int32 itemcode, FString TargetChar)
{
	if (CurItems.Contains(itemcode) && GetItemQuantity(itemcode) >= 1)
	{
		FItemInformation info = GetItemInfo(itemcode);
		FCharInfo CharInfo = GetCharInfo(TargetChar);
		if (info.bCanUse)
		{
			for (auto tuple : info.ItemStat)
			{
				switch (tuple.Key)
				{
				case EStatusType::EST_HP:
					CharInfo.IncreaseHP(tuple.Value);
					break;
				case EStatusType::EST_SP:
					CharInfo.IncreaseSP(tuple.Value);
					break;
				}
			}
			if (SetCharInfo(std::move(CharInfo)))
			{
				CurItems[itemcode] -= 1;
				return true;
			}
		}
	}
	return false;
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
