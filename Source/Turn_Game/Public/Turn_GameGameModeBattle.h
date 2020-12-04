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
class UGI_Archive;

UCLASS()
class TURN_GAME_API ATurn_GameGameModeBattle : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATurn_GameGameModeBattle();

protected:
	virtual void BeginPlay() override;

public:
	virtual void PatternChecking(FUiInfo uiInfo);	// 1. 행동을 취할 플레이어가 몇번째 플레이어인지, 2. 어떠한 행동을 취할지

public:
	UFUNCTION(BlueprintCallable, Category = "Model")
		USkeletalMesh* GetCharMesh(FString CharName, ABattleChar* ToSet);

protected:
	UFUNCTION(BlueprintCallable)
		virtual void SetCharMesh(const TArray<FString>& CharName);

	void GetCharsMesh(const TArray<FString>& CharNames);
	void OnMeshLoadComplete(const TArray<FString>& CharNames);
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BattlePawn")
		TSubclassOf<ABattleChar> BattlePawnClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BattlePawnAI")
		TSubclassOf<ABattleChar> BattlePawnAIClass;

private:
	ABattleChar* MeshLoadChar;
	TArray<FCharInfo> activeCharArray;	// 행동중인 캐릭터들의 Charinfo배열들.

	TArray<ABattleChar*> PlayerArray;	// 플레이어폰 배열			// Y : -300
	TArray<ABattleChar*> EnemyArray;	// 적폰 배열				// Y : 460

	UGI_Archive* archive;
};
