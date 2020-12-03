// Fill out your copyright notice in the Description page of Project Settings.


#include "Turn_GameGameModeBattle.h"
#include "Kismet/GameplayStatics.h"
#include "../GI_Archive.h"
#include "BattleChar.h"

void ATurn_GameGameModeBattle::BeginPlay()
{
	Super::BeginPlay();

	
}

USkeletalMesh * ATurn_GameGameModeBattle::GetCharMesh(FString CharName, ABattleChar * ToSet)
{
	UGI_Archive* GameInst = Cast<UGI_Archive>(GetGameInstance());
	if (GameInst)
	{
		auto Mesh = GameInst->QueryModel(CharName);
		if (Mesh.IsSet())
			return Mesh.Get(nullptr);
		else
		{
			MeshLoadChar = ToSet;
			GameInst->MeshLoadDelegate.BindUFunction(this, L"SetCharMesh");
			return nullptr;
		}
	}
	return nullptr;
}

void ATurn_GameGameModeBattle::SetCharMesh(const TArray<FString>& CharName)
{
	UGI_Archive* GameInst = Cast<UGI_Archive>(GetGameInstance());
	if (GameInst)
	{
		auto mesh = GameInst->QueryModel(CharName[0]);
		if (MeshLoadChar && mesh.IsSet())
			MeshLoadChar->MeshComp->SetSkeletalMesh(mesh.GetValue());
		//MeshLoadChar->GetMesh()->SetSkeletalMesh(mesh.GetValue());
	}
}
