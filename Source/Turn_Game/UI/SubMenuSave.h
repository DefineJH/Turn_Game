// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SubMenuParent.h"
#include "SubMenuSave.generated.h"

/**
 * 
 */

class UVerticalBox;

UCLASS()
class TURN_GAME_API USubMenuSave : public USubMenuParent
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	virtual void ConstructSubWidget() override;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UUserWidget> SaveSlotWidgetClass;
	//저장슬롯 위젯들을 담는 버티컬박스
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UVerticalBox* SaveSlotLayoutBox;
};
