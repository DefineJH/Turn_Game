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

	//BattlePawnClass로 지정한 것이 있을 때 실행.
	if (BattlePawnClass)
	{
		//GetWorld() : UWorld 객체를 가져오는 함수.
		PlayerArray.Push(GetWorld()->SpawnActor<ABattleChar>(BattlePawnClass, FVector(550.0f, -300.0f, 108.0f), FRotator(0.0f, 0.0f, 0.0f)));
		PlayerArray.Push(GetWorld()->SpawnActor<ABattleChar>(BattlePawnClass, FVector(200.0f, -300.0f, 108.0f), FRotator(0.0f, 0.0f, 0.0f)));
		PlayerArray.Push(GetWorld()->SpawnActor<ABattleChar>(BattlePawnClass, FVector(-150.0f, -300.0f, 108.0f), FRotator(0.0f, 0.0f, 0.0f)));
		PlayerArray.Push(GetWorld()->SpawnActor<ABattleChar>(BattlePawnClass, FVector(-500.0f, -300.0f, 108.0f), FRotator(0.0f, 0.0f, 0.0f)));
	}
	
	/*if (BattlePawnAIClass)
	{
		EnemyArray.Push(GetWorld()->SpawnActor<ABattleChar>(BattlePawnAIClass, FVector(550.0f, 460.0f, 108.0f), FRotator(0.0f, 0.0f, 180.0f)));
	}*/

	// 출전중인 플레이어들의 정보를 받아서 activeCharArray에 담아줌.
	if (archive)
	{
		activeCharArray = archive->GetActiveCharsInfo();

		TArray<FString> tempCharName;
		for (int32 i = 0; i < activeCharArray.Num(); i++)
		{
			tempCharName.Add(activeCharArray[i].Name);		// 출전중인 캐릭터들의 이름만 따로 빼옴.
		}
		GetCharsMesh(tempCharName);
	}
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
