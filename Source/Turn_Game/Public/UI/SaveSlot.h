// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SaveSlot.generated.h"

/**
 * 
 */

class UGameSaver;
class UGI_Archive;
class UTextBlock;
class UImage;
class UPartyCharDisplay;
UCLASS()
class TURN_GAME_API USaveSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void ConstructFromData(int idx ,UGI_Archive* archive);
protected:
	/* 해당 슬롯이 존재하지 않을 시 기본 프리뷰를 구성하는 메서드 */
	void ConstructInvalidData(UGI_Archive* archive);
protected:
	UGameSaver* SaveInst;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* SlotIndex;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* PlayTime;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* Thumbnail;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UPartyCharDisplay* MainChar;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite)
	int saveidx;
};
