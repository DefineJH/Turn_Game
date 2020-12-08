// Fill out your copyright notice in the Description page of Project Settings.


#include "Turn_GameGameModeBattle.h"
#include "Kismet/GameplayStatics.h"
#include "../GI_Archive.h"
#include "BattleChar.h"

ATurn_GameGameModeBattle::ATurn_GameGameModeBattle()
{
	PlayerArray.Reserve(4);
	EnemyArray.Reserve(4);
}

void ATurn_GameGameModeBattle::BeginPlay()
{
	Super::BeginPlay();
	archive = Cast<UGI_Archive>(GetGameInstance());

	//BattlePawnClass�� ������ ���� ���� �� ����.
	if (BattlePawnClass)
	{
		//GetWorld() : UWorld ��ü�� �������� �Լ�.
		PlayerArray.Push(GetWorld()->SpawnActor<ABattleChar>(BattlePawnClass, FVector(550.0f, -300.0f, 108.0f), FRotator(0.0f, 0.0f, 0.0f)));
		PlayerArray.Push(GetWorld()->SpawnActor<ABattleChar>(BattlePawnClass, FVector(200.0f, -300.0f, 108.0f), FRotator(0.0f, 0.0f, 0.0f)));
		PlayerArray.Push(GetWorld()->SpawnActor<ABattleChar>(BattlePawnClass, FVector(-150.0f, -300.0f, 108.0f), FRotator(0.0f, 0.0f, 0.0f)));
		PlayerArray.Push(GetWorld()->SpawnActor<ABattleChar>(BattlePawnClass, FVector(-500.0f, -300.0f, 108.0f), FRotator(0.0f, 0.0f, 0.0f)));
	}
	
	/*if (BattlePawnAIClass)
	{
		EnemyArray.Push(GetWorld()->SpawnActor<ABattleChar>(BattlePawnAIClass, FVector(550.0f, 460.0f, 108.0f), FRotator(0.0f, 0.0f, 180.0f)));
	}*/

	// �������� �÷��̾���� ������ �޾Ƽ� activeCharArray�� �����.
	if (archive)
	{
		activeCharArray = archive->GetActiveCharsInfo();

		TArray<FString> tempCharName;
		for (int32 i = 0; i < activeCharArray.Num(); i++)
		{
			tempCharName.Add(activeCharArray[i].Name);		// �������� ĳ���͵��� �̸��� ���� ����.
		}
		GetCharsMesh(tempCharName);
	}
}

void ATurn_GameGameModeBattle::PatternChecking(FUiInfo uiInfo)
{
	// �ε��� ������ ���, ������ �� �÷��̾ ã�Ƽ�, �����ؾ��ϴ� �ൿ�� �Ѱ��ش�.
	FActionInfo tempActionInfo = PlayerArray[uiInfo.iPlayerIndex]->PatternSetting(uiInfo);
	

	///// �������޴� ���� ///////
	//���Ͽ��� ���� Ÿ���� ���� ���,
	if (tempActionInfo.eTargetType == ETargetType::E_Enemy)
	{
		//EnemyArray[tempActionInfo.iTargetIndex]
	}
	// Ÿ���� �÷��̾��� ���,
	else if (tempActionInfo.eTargetType == ETargetType::E_Player)
	{
		// ������
		float fDamage;
		fDamage = tempActionInfo.fAtt - activeCharArray[tempActionInfo.iTargetIndex].fDef;
		if (fDamage <= 0)
			fDamage = 0.0f;

		activeCharArray[tempActionInfo.iTargetIndex].iHP -= fDamage;
		//// ����� ���� ��ī�̺꿡 �Ѱܼ� ���Ž�����.
		//archive->SetCharInfo(activeCharArray[tempActionInfo.iTargetIndex]);
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

void ATurn_GameGameModeBattle::GetCharsMesh(const TArray<FString>& CharNames)
{
	// �𵨵��� ���� �ε��Ǿ� ���� �� true, �ƴҶ� false��ȯ�̹Ƿ� ���� �ε��� �ƴ� false�϶� ��������Ʈ ��Ͻ�Ŵ.
	if (!archive->LoadModels(CharNames))
		archive->MeshLoadDelegate.BindUFunction(this, L"OnMeshComplete");
	else
		OnMeshLoadComplete(CharNames);

}

void ATurn_GameGameModeBattle::OnMeshLoadComplete(const TArray<FString>& CharNames)
{
	for (int i = 0; i < CharNames.Num(); i++)
	{
		PlayerArray[i]->SetCharMesh(archive->QueryModel(CharNames[i]).GetValue());
	}

	////test
	//if (EnemyArray[0])
	//{
	//	EnemyArray[0]->SetCharMesh(archive->QueryModel(CharNames[0]).GetValue());
	//}
}
