// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Public/Custom/CusomEnum.h"
#include "InvenView.generated.h"

/**
 * 
 */

class UListView;
class USingleItem;
UCLASS()
class TURN_GAME_API UInvenView : public UUserWidget
{
	GENERATED_BODY()
public:
	void ConstructList(EItemType CategoryType);
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UListView* ItemListView;

};
