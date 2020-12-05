// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "SingleItem.generated.h"
/**
 * 
 */


class UImage;
class UTextBlock;
class UItemDataObject;

UCLASS()
class TURN_GAME_API USingleItem : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
public:
protected:
	UFUNCTION(BlueprintNativeEvent)
	void NativeOnItemSelectionChanged(bool bIsSelected) override;
	virtual void NativeOnListItemObjectSet(UObject* ItemObj) override;
protected:
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ItemImage;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemName;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemQuantity;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemDesc;

	UItemDataObject* itemData;
};
