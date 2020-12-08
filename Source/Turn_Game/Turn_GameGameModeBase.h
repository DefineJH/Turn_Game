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
	* 모델의 스켈레탈 메쉬를 받아온다 nullptr반환가능, 하지만 nullptr 반환하면 자동적으로 메쉬세팅 가능
	* @param - CharName 캐릭터의 이름
	* @ToSet - 메쉬를 세팅할 캐릭터의 포인터 (보통 this)
	*/
	UFUNCTION(BlueprintCallable, Category = "Model")
	USkeletalMesh* GetCharMesh(FString CharName, AExplorerChar* ToSet);

protected:
	virtual void BeginPlay() override;
	/**
	* GetCharMesh nullptr 반환시 (모델 로드 중), 끝날때 실행되는 델리게이트에 등록된 함수
	* MeshLoadChar의 메쉬를 세팅한다
	* @param - CharName GetCharMesh에서 설정한 이름을 배열로 반환( 1개 )
	*/
	UFUNCTION(BlueprintCallable)
	virtual void SetCharMesh(const TArray<FString>& CharName);
private:
	TArray<FString> ActiveChar;
	AExplorerChar* MeshLoadChar;
};
