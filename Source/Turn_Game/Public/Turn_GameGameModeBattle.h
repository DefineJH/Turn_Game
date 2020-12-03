// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
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
	UFUNCTION(BlueprintCallable, Category = "Model")
		USkeletalMesh* GetCharMesh(FString CharName, ABattleChar* ToSet);

protected:
	UFUNCTION(BlueprintCallable)
		virtual void SetCharMesh(const TArray<FString>& CharName);

private:
	ABattleChar* MeshLoadChar;
};
