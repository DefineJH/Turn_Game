// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Public/Custom/CusomEnum.h"
#include "InvenView.generated.h"

/**
 * 
 */
UCLASS()
class TURN_GAME_API UInvenView : public UUserWidget
{
	GENERATED_BODY()
public:
	void ConstructInven(EItemType CategoryType);
};
