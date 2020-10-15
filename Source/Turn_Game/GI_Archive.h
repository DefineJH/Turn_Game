// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Misc/Optional.h"
#include "Engine/StreamableManager.h"
#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GI_Archive.generated.h"

/**
 * 
 */

class USkeletalMesh;
class UDataTable;

UCLASS()
class TURN_GAME_API UGI_Archive : public UGameInstance
{
	GENERATED_BODY()
public:
	//UI에서 출전 캐릭터 목록을 바꿀때 사용
	UFUNCTION(BlueprintCallable, Category = "Generate")
	void LoadModels(TArray<FString> CharName);
	//model이 Archive에 있는지 알아보고 있으면 optional변수에 담아서 반환.
	TOptional<USkeletalMesh*> QueryModel(FString name);
protected:
	//ModelPath_DT를 토대로 모든 모델의 stringpath를 설정
	void ConstructModelPath();
	//초기화 함수
	virtual void Init() override;
private:
	//LoadModel의 delegate함수 bIsLoadCompleted를 true로 바꿔줌
	void OnLoadCompleted();
public:
	//읽어갈 수 있게 true로 해놓음, 현재 요청받은 캐릭터 로딩이 끝날 시에 true로 바뀜
	//캐릭터를 바꾸지 않고 진입시에도 true유지하니까 이거보고 로직 세우면 쌉가능
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool bIsLoadCompleted;
protected:
	//캐릭터이름과 path를 담고 있는 변수, 블루프린트에서 설정
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UDataTable* ModelPath_DT;
	//모델의 이름과 path를 담고있는 map container
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TMap<FString, FStringAssetReference> PathArchive;
	//모델의 이름과 스켈레탈 메쉬 포인터를담고있는 map container
	TMap<FString, USkeletalMesh*> ModelArchive;

	TSharedPtr<FStreamableHandle> StreamHandle;

};
