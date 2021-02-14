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
	// 로딩이 끝났을 경우, 선택이 된 플레이어를 찾아서, 실행해야하는 행동을 넘겨준다.
	FActionInfo tempActionInfo = PlayerArray[uiInfo.iPlayerIndex]->PatternSetting(uiInfo);
	

	///// 데미지받는 과정 ///////
	//패턴에서 나온 타켓이 적일 경우,
	if (tempActionInfo.eTargetType == ETargetType::E_Enemy)
	{
		//EnemyArray[tempActionInfo.iTargetIndex]
	}
	// 타켓이 플레이어일 경우,
	else if (tempActionInfo.eTargetType == ETargetType::E_Player)
	{
		// 데미지
		float fDamage;
		fDamage = tempActionInfo.fAtt - activeCharArray[tempActionInfo.iTargetIndex].fDef;
		if (fDamage <= 0)
			fDamage = 0.0f;

		activeCharArray[tempActionInfo.iTargetIndex].iHP -= fDamage;
		//// 적용된 값을 아카이브에 넘겨서 갱신시켜줌.
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
	// 모델들이 전부 로딩되어 있을 때 true, 아닐때 false반환이므로 전부 로딩이 아닌 false일때 델리게이트 등록시킴.
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

	//BattlePawnClass로 지정한 것이 있을 때 실행.
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
			tempCharName.Add(activeCharArray[i].Name);		// 출전중인 캐릭터들의 이름만 따로 빼옴.
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

	//BattlePawnClass로 지정한 것이 있을 때 실행.
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
			tempCharName.Add(activeCharArray[i].Name);		// 출전중인 캐릭터들의 이름만 따로 빼옴.
		}
		GetCharsMesh(tempCharName);
	}
}
