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

UCLASS()
class TURN_GAME_API USingleItem : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
public:

protected:
	virtual void NativeOnListItemObjectSet(UObject* ItemObj) override;
	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;
protected:
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ItemImage;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemName;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemDesc;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemQuantity;
};
