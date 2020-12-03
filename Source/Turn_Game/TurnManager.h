// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Containers/Queue.h"
#include <iostream>
#include <list>
#include "Public/Custom/CustomStruct.h"
#include "Public/Custom/CusomEnum.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurnManager.generated.h"

UCLASS()
class TURN_GAME_API ATurnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurnManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	virtual void AddTurnInfo(int32 iNumber, FTurnInfo* pTurnInfo);
	virtual void AddTurnInfo(FTurnInfo* pTurnInfo);
	virtual FTurnInfo* FindTurnInfo(int32 iTurnNumber);
	virtual void SortTurnInfo(void);
	virtual void RemoveTurnInfoMap(int32 iIndex);
	virtual void RemoveTurnInfoArr(FTurnInfo* pTurnInfo);
	virtual void RemoveAllTurnInfo(void);

public:
	UFUNCTION(BlueprintCallable)
	virtual void SelectAction(EActionState eAction);

public:
	TArray<FTurnInfo*>	m_ArrTurnMgr;		// TurnManager
	TMap<int32, FTurnInfo*> m_MapTurnMgr;	// TurnManger
	TQueue<int>			m_Que;
	ETurnMgrState		m_eTurnMgrState;
	//TQueue<>


};
