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
class UWidgetSwitcher;

UCLASS()
class TURN_GAME_API USubMenuInventory : public USubMenuParent
{
	GENERATED_BODY()
	
protected:
	virtual void ConstructSubWidget() override;
	virtual void UpdateSubWidget() override;
private:
	void ShowPage(uint8 page);
protected:
	uint8 CurrentPage;
	uint8 MaxPage;
	TArray<UInvenView*> ListCategory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UInvenView> InvenClass;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UWidgetSwitcher* Switcher;
};
