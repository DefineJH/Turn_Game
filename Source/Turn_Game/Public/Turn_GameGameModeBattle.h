// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Custom/CustomStruct.h"
#include "Turn_GameGameModeBattle.generated.h"

/**
 * 
 */

class ABattleChar;

UCLASS()
class TURN_GAME_API ATurn_GameGameModeBattle : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void PatternChecking(int32 iPlayerIndex, int32 iActionIndex);	// 1. �ൿ�� ���� �÷��̾ ���° �÷��̾�����, 2. ��� �ൿ�� ������

public:
	UFUNCTION(BlueprintCallable, Category = "Model")
		USkeletalMesh* GetCharMesh(FString CharName, ABattleChar* ToSet);

protected:
	UFUNCTION(BlueprintCallable)
		virtual void SetCharMesh(const TArray<FString>& CharName);

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BattlePawn")
		TSubclassOf<ABattleChar> BattlePawnClass;

private:
	ABattleChar* MeshLoadChar;
	TArray<FCharInfo> activeCharArray;	// �ൿ���� ĳ���͵��� Charinfo�迭��.

	TArray<ABattleChar*> PlayerArray;	// �÷��̾��� �迭			// Y : -300
	TArray<ABattleChar*> EnemyArray;	// ���� �迭				// Y : 460
};
