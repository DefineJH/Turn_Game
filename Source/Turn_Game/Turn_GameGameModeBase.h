// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Turn_GameGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TURN_GAME_API ATurn_GameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void Save();
	void Load();
	void SetDefaultData();
	const TArray<FString> * const GetActiveChar() const;
	UFUNCTION(BlueprintCallable, Category = "Model")
	USkeletalMesh* GetCharMesh(FString CharName) const;
protected:
	virtual void BeginPlay() override;
private:
	TArray<FString> ActiveChar;
};
