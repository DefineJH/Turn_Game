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
class UButton;
class UTextBlock;
class UWidgetSwitcher;

UCLASS()
class TURN_GAME_API USubMenuInventory : public USubMenuParent
{
	GENERATED_BODY()
public:
	virtual void SetInitalFocus() override;
protected:
	virtual void ConstructSubWidget() override;
	virtual void UpdateSubWidget() override;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void NextPage();
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void PrevPage();
private:
	void ShowPage();
	void SetButtonVisibility();
protected:
	uint8 CurrentPage;
	uint8 MaxPage;
	TArray<UInvenView*> ListCategory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UInvenView> InvenClass;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UWidgetSwitcher* Switcher;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Category;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* PrevBtn;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* NextBtn;
};
