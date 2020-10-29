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
DECLARE_DELEGATE_OneParam(FMeshLoadCompleteSignature, const FString&);

class USkeletalMesh;
class UDataTable;
class UTexture2D;
class UPaperSprite;

UCLASS(Config = Game)
class TURN_GAME_API UGI_Archive : public UGameInstance
{
	GENERATED_BODY()
public:
	/**
	* 캐릭터를 비동기적으로 로딩 ( 로딩 후 OnLoadComplete 호출 )
	* @param CharName - 로딩할 캐릭터의 목록
	* @warning PathDT 에 존재하는 캐릭터만 로딩가능
	*/
	UFUNCTION(BlueprintCallable, Category = "Generate")
	void LoadModels(TArray<FString> CharName);

	/**
	* 로딩된 캐릭터의 메쉬 포인터를 받아오며 로딩이 되지 않았을 시 LoadModels 호출
	* @param Name - 메쉬를 받아올 캐릭터의 이름
	* @return 해당 메쉬 존재시 반환
	*/
	TOptional<USkeletalMesh*> QueryModel(FString name);

	/**
	* 파티 UI 구성을 위해 현재 파티에 존재하는 캐릭터의 정보를 받아오는 메서드
	* @return CurCharInfo 배열에서 파티에 존재하는 캐릭터(bIsInParty)의 정보를 반환
	*/
	TArray<FCharInfo> GetCharInfo() const;

	/**
	* 파티 UI 구성을 위해 현재 파티에 존재하는 캐릭터의 정보를 받아오는 메서드
	* @return CurCharInfo 배열에서 파티에 존재하는 캐릭터(bIsInParty)의 정보를 반환
	*/
	UFUNCTION(BlueprintCallable, Category = "Info")
	FCharInfo GetCharInfo(FString CharName) const;

	/**
	* Map에 저장된 Texture를 받아오는 메서드
	* @param name - 텍스처의 이름
	* @return 만약 없을 시 nullptr 반환 ( TOptional로 변경 필요 )
	*/
	UTexture2D* GetTextureFromName(FString name) const;
	/**
	* Map에 저장된 Sprite를 받아오는 메서드
	* @param name - 텍스처의 이름
	* @return 만약 없을 시 nullptr 반환 ( TOptional로 변경 필요 )
	*/
	UPaperSprite* GetSpriteFromName(FString name) const;

	/**
	* 현재 게임의 데이터를 슬롯에 저장
	* @param idx - 게임 데이터 슬롯 ( 0~2 )
	* @return 저장 성공시 true, 실패시 false
	*/
	UFUNCTION(BlueprintCallable, Category = "Save&Load")
	bool SaveCurrentData(int idx);

	/**
	* UI 구성을 위해 특정슬롯의 세이브데이터를 반환하는 메서드
	* @param idx - 게임 데이터 슬롯 ( 0~2 )
	* @return 해당 슬롯에 데이터 존재x시 nullptr 반환
	*/
	UGameSaver* GetSaveData(int idx);


	/**
	* UI 구성을 위해 특정슬롯의 저장 가능한 세이브슬롯의 개수를 반환하는 메서드
	* @return 최대 저장가능 슬롯개수 반환
	*/
	int8 GetMaxSaveSlot() const;
	
	/**
	* 맵 탐험을 위한 메인 캐릭터 이름을 반환하는 메서드
	* @return UGI_Archive::MainChar반환 ( ini 설정으로 기본 Louis )
	*/
	UFUNCTION(BlueprintCallable, Category = "Character")
	FORCEINLINE FString GetMainChar() const { return MainChar; }
	/**
	* DefaultCharData_DT에 존재하는 캐릭터의 기본 데이터를 FCharInfo로 반환
	* @param CharName - 기본 데이터를 가져올 캐릭터 이름
	* @return 만약 CharName을 가진 행이 데이터 테이블에 존재시 기본 캐릭터 데이터 반환
	*/
	TOptional<FCharInfo> GetDefaultCharData(FString CharName) const;

	//util function - uobject만들어서static function으로 이동
	FString GetFStringFromEnum(FString StrEnumClass,int32 Value);


	UFUNCTION(BlueprintCallable, Category = "Party")
	bool SetActiveChar(UPARAM(ref) FString& CharName);

	UFUNCTION(BlueprintCallable, Category = "Party")
	bool RemoveActiveChar(UPARAM(ref) FString& CharName);

	UFUNCTION(BlueprintCallable, Category = "Party")
	bool IsActiveChar(UPARAM(ref) FString& CharName);

	UFUNCTION(BlueprintCallable, Category = "Character")
	void ChangeMainChar(UPARAM(ref) FString& CharName);
protected:
	/** 모델의 경로를 Map에 담는 메서드*/
	void ConstructModelPath();
	/** 초기화 함수*/
	virtual void Init() override;
private:
	/** LoadModel의 delegate함수 bIsLoadCompleted를 true로 바꿔줌*/
	void OnMeshLoadCompleted();
	/** 해당 인덱스에 세이브 데이터가 존재하는지 체크*/
	bool HasSaveData(int idx);
	/** 게임 시작시 기본적인 캐릭터 정보를 구성 ( 로딩할때 로딩된 데이터에 따라 변환 )*/
	void ConstructDefaultCharData();

public:
	/** LoadModels 에서 로딩을 요청받은 캐릭터 로딩이 끝날 시에 true로 바뀜*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool bIsLoadCompleted;

	FMeshLoadCompleteSignature MeshLoadDelegate;
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
	TMap<FString, UTexture2D*> TextureArchive;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TMap<FString, UPaperSprite*> UISpriteArchive;
	//모델의 이름과 스켈레탈 메쉬 포인터를담고있는 map container
	TMap<FString, USkeletalMesh*> ModelArchive;

	TMap<FString, FCharInfo> CurCharInfo;
	TArray<FString> CurActiveChar;
	UPROPERTY(Config)
	FString MainChar;

private:
	TSharedPtr<FStreamableHandle> StreamHandle;

	const char MaxSaveSlot = 3;
};


