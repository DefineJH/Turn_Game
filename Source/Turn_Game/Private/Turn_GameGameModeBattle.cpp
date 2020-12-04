// Fill out your copyright notice in the Description page of Project Settings.


#include "Turn_GameGameModeBattle.h"
#include "Kismet/GameplayStatics.h"
#include "../GI_Archive.h"
#include "BattleChar.h"

void ATurn_GameGameModeBattle::BeginPlay()
{
	Super::BeginPlay();

	

	if (BattlePawnClass)
	{
		//GetWorld() : UWorld ��ü�� �������� �Լ�.
		ABattleChar* aTemp;
		aTemp = GetWorld()->SpawnActor<ABattleChar>(BattlePawnClass, FVector(550.0f, -300.0f, 108.0f), FRotator());
	}
}

void ATurn_GameGameModeBattle::PatternChecking(int32 iPlayerIndex, int32 iActionIndex)
{
	UGI_Archive* GameInst = Cast<UGI_Archive>(GetGameInstance());

	if (GameInst)
	{
		activeCharArray = GameInst->GetActiveCharsInfo();	// GI_Archive���� �������� ĳ���͵��� CharsInfo�� �޾ƿ�.

		TArray<FString> tempCharName;						// �޾ƿ� CharsInfo���� LoadModels�� �ʿ��� FString�� Name�鸸 ���� �޾Ƴ� ���.
		int32 ArryNumber = activeCharArray.Num();			// �������� ĳ���͵��� ����.

		for (int32 i = 0; i < ArryNumber; i++)
		{
			tempCharName[i] = activeCharArray[i].Name;		// �������� ĳ���͵��� �̸��� ���� ����.
		}

		//GameInst->LoadModels(tempCharName);
		//GameInst->MeshLoadDelegate.BindUFunction(this, L"LoadModels"); // �� ��, 
	}
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
