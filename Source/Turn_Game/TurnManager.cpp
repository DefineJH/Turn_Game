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
	// TArray�� Add�� Emplace�� �迭�� �߰��� �� �ִµ�, Emplace�� �ַ� ����� ����

	//m_ArrTurnMgr.Emplace(iNumber, pTurnInfo);
	//����ü�� �ּҸ� �Ѱܹ޾��� ���, �̹� �޾Ҵ� ���ͳ� �÷��̾��� ��� ��� ó���� ���ΰ�? (UI���� �ص��ɵ�)
}

void ATurnManager::AddTurnInfo(FTurnInfo * pTurnInfo)
{
	// TArray�� Add�� Emplace�� �迭�� �߰��� �� �ִµ�, Emplace�� �ַ� ����� ����

	m_ArrTurnMgr.Emplace(pTurnInfo);
}

FTurnInfo* ATurnManager::FindTurnInfo(int32 iTurnNumber)
{


	return nullptr;
}

void ATurnManager::SortTurnInfo(void)
{
	//TMap�� ����� ��� Key������ ������ ����, �̷� ��� ���ǵ尪�� Key������ �����ؼ� ������ ������. �ٵ� ���� ������ ����� �÷��̾��� ����� ���ǵ尡 ���ٸ�? ����

	m_ArrTurnMgr.Sort([](const FTurnInfo& A, const FTurnInfo& B) {
		return A.iSpeed < B.iSpeed;
	});
}

void ATurnManager::RemoveTurnInfoMap(int32 iIndex)
{
}

void ATurnManager::RemoveTurnInfoArr(FTurnInfo * pTurnInfo)
{
	//TArry�� ����� ��� �����Ҷ� ����
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
