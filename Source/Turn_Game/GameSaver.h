// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Public/Custom/CustomStruct.h"
#include "GameFramework/SaveGame.h"
#include "GameSaver.generated.h"

/**
 * 
 */
UCLASS()
class TURN_GAME_API UGameSaver : public USaveGame
{
	GENERATED_BODY()
public:
	FCharInfo GetCharInfo(FString name) const;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	FString SaveSlotName;		// Save game data file name

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	int32 SaveIndex;		// Save game data file index

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	TArray<FCharInfo> CharInfos;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	TArray<FString> ActiveChar;

	/** key - ItemCode , value - Amount*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	TMap<int32, int32> Items;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	FString MainChar;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	FString SaveMap;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	FString SavePoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	uint8 PlayTime_H;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	uint8 PlayTime_M;

};
