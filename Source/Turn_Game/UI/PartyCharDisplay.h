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
class UProgressBar;
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
	UImage* Image_Char;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* Elemental;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* Image_Select;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Name;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Level;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Text_HP;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Text_SP;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* Text_EXP;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* Progress_HP;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* Progress_SP;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* Progress_EXP;

};
