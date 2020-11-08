// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../Public/Custom/CustomStruct.h"
#include "ItemDataObject.generated.h"

/**
 * 
 */
UCLASS()
class TURN_GAME_API UItemDataObject : public UObject
{
	GENERATED_BODY()
public:
	const FItemInformation GetInfo() const;
	void SetInfo(FItemInformation inInfo);
private:
	FItemInformation info;
};
