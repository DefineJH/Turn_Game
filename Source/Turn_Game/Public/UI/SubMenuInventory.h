// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SubMenuParent.h"
#include "SubMenuInventory.generated.h"

/**
 * 
 */

class UInvenView;

UCLASS()
class TURN_GAME_API USubMenuInventory : public USubMenuParent
{
	GENERATED_BODY()
	
protected:

	TArray<UInvenView*> CategoryWidgets;

	virtual void ConstructSubWidget() override;
	virtual void UpdateSubWidget() override;
};
