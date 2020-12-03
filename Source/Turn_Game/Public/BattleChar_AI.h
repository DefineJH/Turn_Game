// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleChar.h"
#include "BattleChar_AI.generated.h"

/**
 * 
 */
UCLASS()
class TURN_GAME_API ABattleChar_AI : public ABattleChar
{
	GENERATED_BODY()

public:
	ABattleChar_AI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
