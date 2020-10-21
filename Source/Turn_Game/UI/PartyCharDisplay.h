// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PartyCharDisplay.generated.h"

/**
 * 
 */

class UImage;
class UTextBlock;
class UGI_Archive;
struct FCharInfo;

UCLASS()
class TURN_GAME_API UPartyCharDisplay : public UUserWidget
{
	GENERATED_BODY()
public:
	void ConstructByData(FCharInfo info, UGI_Archive* archive);

	void ConstructByData(TOptional<FCharInfo> info, UGI_Archive* archive);

protected:
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* CharImage;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* Elemental;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Name;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Level;
};
