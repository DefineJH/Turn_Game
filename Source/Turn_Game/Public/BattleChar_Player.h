// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleChar.h"
#include "BattleChar_Player.generated.h"

/**
 * 
 */
UCLASS()
class TURN_GAME_API ABattleChar_Player : public ABattleChar
{
	GENERATED_BODY()

public:
	ABattleChar_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
