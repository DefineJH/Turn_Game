// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Misc/Optional.h"
#include "GameSaver.h"
#include "Engine/StreamableManager.h"
#include "Engine/DataTable.h"
#include "Custom/CustomStruct.h"
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GI_Archive.generated.h"

/**
 * 
 */

class USkeletalMesh;
class UDataTable;
class UTexture2D;
class UPaperSprite;

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

	//파티 UI 구성하기 위해 캐릭터의 정보 전송하는 메서드
	TArray<FCharInfo> GetCharInfo() const;
	//텍스처를 가져오는 메서드
	UTexture2D* GetTextureFromName(FString name) const;
	//텍스처를 가져오는 메서드
	UPaperSprite* GetSpriteFromName(FString name) const;

	//개임의 세이브 기능
	bool SaveCurrentData(int idx);
	//프리뷰 구성을 위해 세이브 데이터 슬롯을 가져온다
	UGameSaver* GetSaveData(int idx);
	//최대 세이브 슬롯을 전송
	int8 GetMaxSaveSlot() const;
	


	//util function - uobject만들어서static function으로 이동
	FString GetFStringFromEnum(FString StrEnumClass,int32 Value);
protected:
	//ModelPath_DT를 토대로 모든 모델의 stringpath를 설정
	void ConstructModelPath();
	//초기화 함수
	virtual void Init() override;
private:
	//LoadModel의 delegate함수 bIsLoadCompleted를 true로 바꿔줌
	void OnMeshLoadCompleted();
	//해당 인덱스에 세이브 데이터가 존재하는지 체크
	bool HasSaveData(int idx);
	//게임 시작시 기본적인 캐릭터 정보를 구성 ( 로딩할때 로딩된 데이터에 따라 변환 )
	void ConstructDefaultCharData();
public:
	//읽어갈 수 있게 true로 해놓음, 현재 요청받은 캐릭터 로딩이 끝날 시에 true로 바뀜
	//캐릭터를 바꾸지 않고 진입시에도 true유지하니까 이거보고 로직 세우면 쌉가능
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool bIsLoadCompleted;
protected:
	//캐릭터이름과 path를 담고 있는 변수, 블루프린트에서 설정
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UDataTable* ModelPath_DT;

	//기본 캐릭터 데이터를 담고있는 데이터 테이블
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UDataTable* DefaultCharData_DT;

	//모델의 이름과 path를 담고있는 map container
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TMap<FString, FStringAssetReference> PathArchive;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TMap<FString, UTexture2D*> UICharImgArchive;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TMap<FString, UPaperSprite*> UISpriteArchive;
	//모델의 이름과 스켈레탈 메쉬 포인터를담고있는 map container
	TMap<FString, USkeletalMesh*> ModelArchive;

	TMap<FString, FCharInfo> CurCharInfo;
	TArray<FString> CurActiveChar;

private:
	TSharedPtr<FStreamableHandle> StreamHandle;

	const char MaxSaveSlot = 3;
};


