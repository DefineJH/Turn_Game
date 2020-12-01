// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnManager.h"

// Sets default values
ATurnManager::ATurnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATurnManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATurnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATurnManager::AddTurnInfo(int32 iNumber, FTurnInfo* pTurnInfo)
{
	// TArray는 Add와 Emplace로 배열에 추가할 수 있는데, Emplace를 주로 사용할 예정

	//m_ArrTurnMgr.Emplace(iNumber, pTurnInfo);
	//구조체의 주소를 넘겨받았을 경우, 이미 받았던 몬스터나 플레이어일 경우 어떻게 처리할 것인가? (UI에서 해도될듯)
}

void ATurnManager::AddTurnInfo(FTurnInfo * pTurnInfo)
{
	// TArray는 Add와 Emplace로 배열에 추가할 수 있는데, Emplace를 주로 사용할 예정

	m_ArrTurnMgr.Emplace(pTurnInfo);
}

FTurnInfo* ATurnManager::FindTurnInfo(int32 iTurnNumber)
{


	return nullptr;
}

void ATurnManager::SortTurnInfo(void)
{
	//TMap을 사용할 경우 Key값으로 솔팅이 가능, 이럴 경우 스피드값을 Key값으로 지정해서 솔팅이 가능함. 근데 만약 몬스터의 기술과 플레이어의 기술의 스피드가 같다면? ㅆㅃ

	m_ArrTurnMgr.Sort([](const FTurnInfo& A, const FTurnInfo& B) {
		return A.iSpeed < B.iSpeed;
	});
}

void ATurnManager::RemoveTurnInfoMap(int32 iIndex)
{
}

void ATurnManager::RemoveTurnInfoArr(FTurnInfo * pTurnInfo)
{
	//TArry을 사용할 경우 제거할때 빡셈
	m_ArrTurnMgr.Remove(pTurnInfo);
}

void ATurnManager::RemoveAllTurnInfo(void)
{
	int32 iSize = m_ArrTurnMgr.Num();

	while (iSize > 0)
	{
		m_ArrTurnMgr.RemoveAt(iSize);
		iSize--;
	}

}

void ATurnManager::SelectAction(EActionState eAction)
{

}
