// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Turn_GameGameModeBase.generated.h"

/**
 * 
 */

class AExplorerChar;

UCLASS()
class TURN_GAME_API ATurn_GameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void Save(int idx);
	void Load(int idx);
	void SetDefaultData();
	const TArray<FString> * const GetActiveChar() const;
	UFUNCTION(BlueprintCallable, Category = "Model")
	USkeletalMesh* GetCharMesh(FString CharName, AExplorerChar* ToSet);
protected:
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	virtual void SetCharMesh(const TArray<FString>& CharName);
private:
	TArray<FString> ActiveChar;
	AExplorerChar* MeshLoadChar;
};
