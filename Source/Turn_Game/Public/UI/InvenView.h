// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Public/Custom/CusomEnum.h"
#include "../Public/Custom/CustomStruct.h"
#include "InvenView.generated.h"

/**
 * 
 */

class UListView;
class USingleItem;
class UItemDataObject;
class UTextBlock;
class UScrollBox;
class UWidgetSwitcher;

UCLASS()
class TURN_GAME_API UInvenView : public UUserWidget
{
	GENERATED_BODY()
public:
	void ConstructList(EItemType CategoryType);
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SelectItem(UItemDataObject* SelectedItem);
	void SetFocus();
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UListView* ItemListView;
	UPROPERTY(BlueprintReadWrite)
	FItemInformation ItemData;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSubclassOf<UUserWidget> MiniChar;
	bool LeftSwitch;
};
