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
DECLARE_DELEGATE_OneParam(FMeshLoadCompleteSignature, const TArray<FString>&);
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
	* @return 모델들이 전부 로딩되어 있을 때 true -> QueryModel 실행 시 메쉬획득, 아닐때 false반환-> 이 때 MeshLoadDelegate에 로딩 완료시 함수 등록
	*/
	UFUNCTION(BlueprintCallable, Category = "Generate")
	bool LoadModels(TArray<FString> CharName);

	UFUNCTION(BlueprintCallable, Category = "Generate")
	bool LoadModel(FString CharName);

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
	UFUNCTION(BlueprintCallable, Category = "Info")
	TArray<FCharInfo> GetPartyCharsInfo() const;

	/**
	* 배틀 씬 구성을 위해 현재 출전중인 캐릭터의 정보를 받아오는 메서드
	* @return CurCharInfo 배열에서 파티에 존재하는 캐릭터(bIsActive)의 정보를 반환
	*/
	UFUNCTION(BlueprintCallable, Category = "Info")
	TArray<FCharInfo> GetActiveCharsInfo() const;


	/**
	* 현재 파티에 존재하는 캐릭터의 정보를 받아오는 메서드
	* @return CurCharInfo 배열에서 파티에 존재하는 캐릭터(bIsInParty)의 정보를 반환
	*/
	UFUNCTION(BlueprintCallable, Category = "Info")
	const FCharInfo& GetCharInfo(FString CharName) const;
	/**
	* 캐릭터의 정보를 아카이브에 저장 ( 세이브,메인 씬 UI 구성 시 사용 )
	* @param CharInfo - 저장할 캐릭터의 정보
	* @return 캐릭터 정보 배열에 매개변수 캐릭터의 이름이 없을 시 false 반환
	*/
	UFUNCTION(BlueprintCallable, Category = "Info")
	bool SetCharInfo(FCharInfo CharInfo);

	/**
	* Map에 저장된 Texture를 받아오는 메서드
	* @param name - 텍스처의 이름
	* @return 만약 없을 시 nullptr 반환 ( TOptional로 변경 필요 )
	*/
	UFUNCTION(BlueprintCallable, Category = "UI")
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


	/**
	* 넘겨받은 아이템 코드를 가진 아이템의 정보를 반환한다
	* @param itemCode - 아이템 코드 ( DT에서 확인가능 )
	* @return 받은 아이템 코드의 정보를 반환( 아카이브 map의 tuple의 레퍼런스 )
	*/
	UFUNCTION(BlueprintCallable, Category = "Item")
	const FItemInformation& GetItemInfo(int32 itemCode) const;

	/**
	* 현재 보유하고 있는 아이템의 개수
	* @param itemCode - 아이템 코드
	* @return 아이템 수량
	*/
	UFUNCTION(BlueprintCallable, Category = "Item")
	int32 GetItemQuantity(int32 itemCode) const;
	/**
	* 아카이브에 존재하는 모든 아이템을 매개변수로 받은 카테고리에 의해 분류하여 반환
	* @param EItemType type - 아이템 타입
	* @return 아이템 수량
	*/
	UFUNCTION(BlueprintCallable, Category = "Item")
	TArray<FItemInformation> GetItemInfoByCategory(EItemType type);

	/**
	* 현재 보유하고 있는 아이템을 카테고리별로 반환
	* @param type - 아이템 타입 열거형
	* @return 아이템 인포메이션 구조체가 담긴 배열
	*/
	UFUNCTION(BlueprintCallable, Category = "Item")
	TArray<FItemInformation> GetCurItemInfoByCategory(EItemType type);

	//util function - uobject만들어서static function으로 이동
	static FString GetFStringFromEnum(FString StrEnumClass,int32 Value);

	/**
	* 아이템을 지정한 플레이어에 사용
	* @param type - 아이템 타입 열거형
	* @return 아이템 인포메이션 구조체가 담긴 배열
	*/
	UFUNCTION(BlueprintCallable)
	bool UseItem(int32 itemcode, FString TargetChar);

	/**
	* 현재 게임의 정보를 매개변수로 받은 데이터에 의거해 재구축
	* @param LoadData - 로드한 게임의 정보가 담긴 인스턴스의 포인터
	*/
	void LoadGameFromData(UGameSaver* LoadData);
protected:
	/** 모델의 경로를 Map에 담는 메서드*/
	void ConstructModelPath();
	/** 아이템 정보를 DT에서 구성하여 Map에 담는 메서드*/
	void ConstructItemInfo();

	void ConstructMonsterInfo();

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

	/**적 정보를 담고있는 데이터 테이블*/
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UDataTable* Enemy_DT;


	/**모델의 이름과 path를 담고있는 map container*/
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TMap<FString, FStringAssetReference> PathArchive;

	/**게임에 사용되는 텍스처를 모아놓은 맵, 에디터에서 추가*/
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TMap<FString, UTexture2D*> TextureArchive;

	/**게임의 UI 에 사용되는 스프라이트들을 모아놓은 맵, 에디터에서 추가*/
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TMap<FString, UPaperSprite*> UISpriteArchive;

	UPROPERTY()
	/**모델의 이름과 스켈레탈 메쉬 포인터를담고있는 map container*/
	TMap<FString, USkeletalMesh*> ModelArchive;

	UPROPERTY()
	/**현재 진행중인 게임의 캐릭터 정보를 담고있는 map container*/
	TMap<FString, FCharInfo> CurCharInfo;

	UPROPERTY()
	/**몬스터의 정보를 담고있는 컨테이너*/
	TMap<FString, FEnemyInfo> EnemyInfo;

	UPROPERTY()
	/**현재 진행중인 게임의 출전(bisActive) 캐릭터 이름을 담고있는 배열*/
	TArray<FString> CurActiveChar;

	UPROPERTY()
	/**게임 상에 존재하는 모든 아이템의 정보를 담고있는 배열*/
	TArray<FItemInformation> ItemInfos;

	UPROPERTY()
	/**key - item code, value - item count*/
	TMap<int32, uint8> CurItems;

	UPROPERTY(Config)
	FString MainChar;

private:
	TSharedPtr<FStreamableHandle> StreamHandle;

	const char MaxSaveSlot = 3;

	TArray<FString> LoadChars;
};


