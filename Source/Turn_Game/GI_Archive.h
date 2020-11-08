// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Misc/Optional.h"
#include "GameSaver.h"
#include "Engine/StreamableManager.h"
#include "Engine/DataTable.h"
#include "Public/Custom/CustomStruct.h"
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GI_Archive.generated.h"

/**
 * 
 */

 /**캐릭터 비동기 로딩 끝날 시 Execute 되는 델리게이트 */
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


	/**
	* 넘겨받은 캐릭터를 출전목록에 추가한다 
	* @param CharName - 캐릭터 이름
	* @return CurActiveChar가 3 이상이거나 현재 캐릭터가 이미 출전목록에 있으면 false 반환 , 성공시 true
	*/
	UFUNCTION(BlueprintCallable, Category = "Party")
	bool SetActiveChar(UPARAM(ref) FString& CharName);

	/**
	* 넘겨받은 캐릭터를 출전목록에서 제거한다
	* @param CharName - 캐릭터 이름
	* @return CurActiveChar가 0 이거나 현재 캐릭터가 이미 출전목록에 없으면 false 반환 , 성공시 true
	*/
	UFUNCTION(BlueprintCallable, Category = "Party")
	bool RemoveActiveChar(UPARAM(ref) FString& CharName);
	/**
	* 넘겨받은 캐릭터가 출전목록에 들어가 있는지 확인한다
	* @param CharName - 캐릭터 이름
	* @return 출전목록에 존재하면 true, 아닐시 false 반환
	*/
	UFUNCTION(BlueprintCallable, Category = "Party")
	bool IsActiveChar(UPARAM(ref) FString& CharName) const;

	/**
	* 넘겨받은 캐릭터를 레벨을 탐험하는 캐릭터로 설정한다
	* @param CharName - 캐릭터 이름
	* @return 출전목록에 존재하면 true, 아닐시 false 반환
	*/
	UFUNCTION(BlueprintCallable, Category = "Character")
	void ChangeMainChar(UPARAM(ref) FString& CharName);


	UFUNCTION(BlueprintCallable, Category = "Item")
	const FItemInformation& GetItemInfo(int32 itemCode) const;

	int8 GetItemQuantity(int32 itemCode) const;

	UFUNCTION(BlueprintCallable, Category = "Item")
	TArray<FItemInformation> GetItemInfoByCategory(EItemType type);

	
	UFUNCTION(BlueprintCallable, Category = "Item")
	TArray<FItemInformation> GetCurItemInfoByCategory(EItemType type);

	//util function - uobject만들어서static function으로 이동
	FString GetFStringFromEnum(FString StrEnumClass,int32 Value);
protected:
	/** 모델의 경로를 Map에 담는 메서드*/
	void ConstructModelPath();

	void ConstructItemInfo();

	/** 초기화 함수*/
	virtual void Init() override;
private:
	/** LoadModel의 delegate함수 bIsLoadCompleted를 true로 바꿔줌*/
	void OnMeshLoadCompleted();
	/** 해당 인덱스에 세이브 데이터가 존재하는지 체크*/
	bool HasSaveData(int idx);
	/** 게임 시작시 기본적인 캐릭터 정보를 구성 ( 로딩할때 로딩된 데이터에 따라 변환 )*/
	void ConstructDefaultCharData();

	void ConstructDefaultData();
public:
	/** LoadModels 에서 로딩을 요청받은 캐릭터 로딩이 끝날 시에 true로 바뀜*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool bIsLoadCompleted;

	/** LoadModels 에서 로딩을 요청받은 캐릭터 로딩이 끝날 시에 실행되는 델리게이트*/
	FMeshLoadCompleteSignature MeshLoadDelegate;
protected:
	/**캐릭터이름과 path를 담고 있는 변수, 블루프린트에서 설정*/
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UDataTable* ModelPath_DT;

	/**기본 캐릭터 데이터를 담고있는 데이터 테이블*/
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UDataTable* DefaultCharData_DT;

	/**아이템 정보를 담고있는 데이터 테이블*/
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UDataTable* ItemData_DT;

	/**모델의 이름과 path를 담고있는 map container*/
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TMap<FString, FStringAssetReference> PathArchive;

	/**게임에 사용되는 텍스처를 모아놓은 맵, 에디터에서 추가*/
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TMap<FString, UTexture2D*> TextureArchive;

	/**게임의 UI 에 사용되는 스프라이트들을 모아놓은 맵, 에디터에서 추가*/
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TMap<FString, UPaperSprite*> UISpriteArchive;

	/**모델의 이름과 스켈레탈 메쉬 포인터를담고있는 map container*/
	TMap<FString, USkeletalMesh*> ModelArchive;

	/**현재 진행중인 게임의 캐릭터 정보를 담고있는 map container*/
	TMap<FString, FCharInfo> CurCharInfo;

	/**현재 진행중인 게임의 출전 캐릭터 이름을 담고있는 배열*/
	TArray<FString> CurActiveChar;

	/**게임 상에 존재하는 모든 아이템의 정보를 담고있는 배열*/
	TArray<FItemInformation> ItemInfos;

	/**key - item code, value - item count*/
	TMap<int32, uint8> CurItems;

	UPROPERTY(Config)
	FString MainChar;

private:
	TSharedPtr<FStreamableHandle> StreamHandle;

	const char MaxSaveSlot = 3;
};


