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

	/**
	* ���� ���̷�Ż �޽��� �޾ƿ´� nullptr��ȯ����, ������ nullptr ��ȯ�ϸ� �ڵ������� �޽����� ����
	* @param - CharName ĳ������ �̸�
	* @ToSet - �޽��� ������ ĳ������ ������ (���� this)
	*/
	UFUNCTION(BlueprintCallable, Category = "Model")
	USkeletalMesh* GetCharMesh(FString CharName, AExplorerChar* ToSet);

protected:
	virtual void BeginPlay() override;
	/**
	* GetCharMesh nullptr ��ȯ�� (�� �ε� ��), ������ ����Ǵ� ��������Ʈ�� ��ϵ� �Լ�
	* MeshLoadChar�� �޽��� �����Ѵ�
	* @param - CharName GetCharMesh���� ������ �̸��� �迭�� ��ȯ( 1�� )
	*/
	UFUNCTION(BlueprintCallable)
	virtual void SetCharMesh(const TArray<FString>& CharName);
private:
	TArray<FString> ActiveChar;
	AExplorerChar* MeshLoadChar;
};
