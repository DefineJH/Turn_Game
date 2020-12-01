// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Turn_GameGameModeBattle.generated.h"

/**
 * 
 */
UCLASS()
class TURN_GAME_API ATurn_GameGameModeBattle : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
};
