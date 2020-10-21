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
class UPartyCharDisplay;
UCLASS()
class TURN_GAME_API USaveSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void ConstructFromData(UGameSaver* SaveData ,UGI_Archive* archive);
protected:
	void ConstructInvalidData(UGI_Archive* archive);
protected:
	UGameSaver* SaveInst;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* SlotIndex;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* PlayTime;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UPartyCharDisplay* MainChar;
};
