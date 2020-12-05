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
class UItemDataObject;
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
	UFUNCTION(BlueprintCallable, Category = "UI")
	void UseCurSelectedItem(FString TargetChar);
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UListView* ItemListView;
	UPROPERTY(BlueprintReadWrite)
	UItemDataObject* SelectedItemData;
	UPROPERTY(BlueprintReadWrite)
	USingleItem* SelectedItemWidget;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TSubclassOf<UUserWidget> MiniChar;

	EItemType invenType;
	bool LeftSwitch;

};
