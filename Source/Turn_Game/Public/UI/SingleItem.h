// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SingleItem.generated.h"

/**
 * 
 */

struct FItemInfo;

UCLASS()
class TURN_GAME_API USingleItem : public UUserWidget
{
	GENERATED_BODY()
public:
	void Construct(FItemInfo info);
};
