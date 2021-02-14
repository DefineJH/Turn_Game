// Fill out your copyright notice in the Description page of Project Settings.


#include "Turn_GameGameModeBattle.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/LevelSequence/Public/LevelSequence.h"
#include "Runtime/LevelSequence/Public/LevelSequencePlayer.h"
#include "BattleChar_Player.h"
#include "../GI_Archive.h"
#include "BattleChar.h"
#include "Engine/TargetPoint.h"

ATurn_GameGameModeBattle::ATurn_GameGameModeBattle()
{
	PlayerArray.Reserve(4);
	EnemyArray.Reserve(4);
}

void ATurn_GameGameModeBattle::BeginPlay()
{
	Super::BeginPlay();
	archive = Cast<UGI_Archive>(GetGameInstance());

	SetUpPlayerPawn();


	PlayStartSequence();
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
		archive->MeshLoadDelegate.BindUFunction(this, L"OnMeshLoadComplete");
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

void ATurn_GameGameModeBattle::PlayStartSequence()
{
	if (StartSequence)
	{
		SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), StartSequence, FMovieSceneSequencePlaybackSettings(), StartSequenceActor);
	}
	if (SequencePlayer)
	{
		SequencePlayer->Play();
	}
}

void ATurn_GameGameModeBattle::SetUpPlayerPawn()
{
	TArray<AActor*> TempTargetPoints;
	TArray<AActor*> TempPlayerPoint;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), TempTargetPoints);

	for (AActor* temp : TempTargetPoints)
	{
		if (temp->GetName().Contains("Player"))
		{
			TempPlayerPoint.Add(temp);
			UE_LOG(LogTemp, Warning, L"%s", *temp->GetName());
		}
	}

	//BattlePawnClass�� ������ ���� ���� �� ����.
	if (BattlePawnClass && archive)
	{
		activeCharArray = archive->GetActiveCharsInfo();

		TArray<FString> tempCharName;
		for (int32 i = 0; i < TempPlayerPoint.Num(); i++)
		{
			if (i >= activeCharArray.Num())
			{
				break;
			}
			PlayerArray.Push(GetWorld()->SpawnActor<ABattleChar_Player>(BattlePawnClass, TempPlayerPoint[i]->GetActorLocation(), FRotator(0.f, 0.f, 0.f)));
			PlayerArray[i]->SetCharInfo(activeCharArray[i]);
			tempCharName.Add(activeCharArray[i].Name);		// �������� ĳ���͵��� �̸��� ���� ����.
		}
		GetCharsMesh(tempCharName);
	}
}

void ATurn_GameGameModeBattle::SetUpEnemyPawn()
{
	TArray<AActor*> TempTargetPoints;
	TArray<AActor*> TempPlayerPoint;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), TempTargetPoints);

	for (AActor* temp : TempTargetPoints)
	{
		if (temp->GetName().Contains("Player"))
		{
			TempPlayerPoint.Add(temp);
			UE_LOG(LogTemp, Warning, L"%s", *temp->GetName());
		}
	}

	//BattlePawnClass�� ������ ���� ���� �� ����.
	if (BattlePawnClass && archive)
	{
		activeCharArray = archive->GetActiveCharsInfo();

		TArray<FString> tempCharName;
		for (int32 i = 0; i < TempPlayerPoint.Num(); i++)
		{
			if (i >= activeCharArray.Num())
			{
				break;
			}
			PlayerArray.Push(GetWorld()->SpawnActor<ABattleChar_Player>(BattlePawnClass, TempPlayerPoint[i]->GetActorLocation(), FRotator(0.f, 0.f, 0.f)));
			PlayerArray[i]->SetCharInfo(activeCharArray[i]);
			tempCharName.Add(activeCharArray[i].Name);		// �������� ĳ���͵��� �̸��� ���� ����.
		}
		GetCharsMesh(tempCharName);
	}
}
