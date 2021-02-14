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

 /**ĳ���� �񵿱� �ε� ���� �� Execute �Ǵ� ��������Ʈ */
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
	* ĳ���͸� �񵿱������� �ε� ( �ε� �� OnLoadComplete ȣ�� )
	* @param CharName - �ε��� ĳ������ ���
	* @warning PathDT �� �����ϴ� ĳ���͸� �ε�����
	* @return �𵨵��� ���� �ε��Ǿ� ���� �� true -> QueryModel ���� �� �޽�ȹ��, �ƴҶ� false��ȯ-> �� �� MeshLoadDelegate�� �ε� �Ϸ�� �Լ� ���
	*/
	UFUNCTION(BlueprintCallable, Category = "Generate")
	bool LoadModels(TArray<FString> CharName);

	UFUNCTION(BlueprintCallable, Category = "Generate")
	bool LoadModel(FString CharName);

	/**
	* �ε��� ĳ������ �޽� �����͸� �޾ƿ��� �ε��� ���� �ʾ��� �� LoadModels ȣ��
	* @param Name - �޽��� �޾ƿ� ĳ������ �̸�
	* @return �ش� �޽� ����� ��ȯ
	*/
	TOptional<USkeletalMesh*> QueryModel(FString name);

	/**
	* ��Ƽ UI ������ ���� ���� ��Ƽ�� �����ϴ� ĳ������ ������ �޾ƿ��� �޼���
	* @return CurCharInfo �迭���� ��Ƽ�� �����ϴ� ĳ����(bIsInParty)�� ������ ��ȯ
	*/
	UFUNCTION(BlueprintCallable, Category = "Info")
	TArray<FCharInfo> GetPartyCharsInfo() const;

	/**
	* ��Ʋ �� ������ ���� ���� �������� ĳ������ ������ �޾ƿ��� �޼���
	* @return CurCharInfo �迭���� ��Ƽ�� �����ϴ� ĳ����(bIsActive)�� ������ ��ȯ
	*/
	UFUNCTION(BlueprintCallable, Category = "Info")
	TArray<FCharInfo> GetActiveCharsInfo() const;


	/**
	* ���� ��Ƽ�� �����ϴ� ĳ������ ������ �޾ƿ��� �޼���
	* @return CurCharInfo �迭���� ��Ƽ�� �����ϴ� ĳ����(bIsInParty)�� ������ ��ȯ
	*/
	UFUNCTION(BlueprintCallable, Category = "Info")
	const FCharInfo& GetCharInfo(FString CharName) const;
	/**
	* ĳ������ ������ ��ī�̺꿡 ���� ( ���̺�,���� �� UI ���� �� ��� )
	* @param CharInfo - ������ ĳ������ ����
	* @return ĳ���� ���� �迭�� �Ű����� ĳ������ �̸��� ���� �� false ��ȯ
	*/
	UFUNCTION(BlueprintCallable, Category = "Info")
	bool SetCharInfo(FCharInfo CharInfo);

	/**
	* Map�� ����� Texture�� �޾ƿ��� �޼���
	* @param name - �ؽ�ó�� �̸�
	* @return ���� ���� �� nullptr ��ȯ ( TOptional�� ���� �ʿ� )
	*/
	UFUNCTION(BlueprintCallable, Category = "UI")
	UTexture2D* GetTextureFromName(FString name) const;
	/**
	* Map�� ����� Sprite�� �޾ƿ��� �޼���
	* @param name - �ؽ�ó�� �̸�
	* @return ���� ���� �� nullptr ��ȯ ( TOptional�� ���� �ʿ� )
	*/
	UPaperSprite* GetSpriteFromName(FString name) const;

	/**
	* ���� ������ �����͸� ���Կ� ����
	* @param idx - ���� ������ ���� ( 0~2 )
	* @return ���� ������ true, ���н� false
	*/
	UFUNCTION(BlueprintCallable, Category = "Save&Load")
	bool SaveCurrentData(int idx);

	/**
	* UI ������ ���� Ư�������� ���̺굥���͸� ��ȯ�ϴ� �޼���
	* @param idx - ���� ������ ���� ( 0~2 )
	* @return �ش� ���Կ� ������ ����x�� nullptr ��ȯ
	*/
	UGameSaver* GetSaveData(int idx);


	/**
	* UI ������ ���� Ư�������� ���� ������ ���̺꽽���� ������ ��ȯ�ϴ� �޼���
	* @return �ִ� ���尡�� ���԰��� ��ȯ
	*/
	int8 GetMaxSaveSlot() const;
	
	/**
	* �� Ž���� ���� ���� ĳ���� �̸��� ��ȯ�ϴ� �޼���
	* @return UGI_Archive::MainChar��ȯ ( ini �������� �⺻ Louis )
	*/
	UFUNCTION(BlueprintCallable, Category = "Character")
	FORCEINLINE FString GetMainChar() const { return MainChar; }

	/**
	* DefaultCharData_DT�� �����ϴ� ĳ������ �⺻ �����͸� FCharInfo�� ��ȯ
	* @param CharName - �⺻ �����͸� ������ ĳ���� �̸�
	* @return ���� CharName�� ���� ���� ������ ���̺� ����� �⺻ ĳ���� ������ ��ȯ
	*/
	TOptional<FCharInfo> GetDefaultCharData(FString CharName) const;


	/**
	* �Ѱܹ��� ĳ���͸� ������Ͽ� �߰��Ѵ� 
	* @param CharName - ĳ���� �̸�
	* @return CurActiveChar�� 3 �̻��̰ų� ���� ĳ���Ͱ� �̹� ������Ͽ� ������ false ��ȯ , ������ true
	*/
	UFUNCTION(BlueprintCallable, Category = "Party")
	bool SetActiveChar(UPARAM(ref) FString& CharName);

	/**
	* �Ѱܹ��� ĳ���͸� ������Ͽ��� �����Ѵ�
	* @param CharName - ĳ���� �̸�
	* @return CurActiveChar�� 0 �̰ų� ���� ĳ���Ͱ� �̹� ������Ͽ� ������ false ��ȯ , ������ true
	*/
	UFUNCTION(BlueprintCallable, Category = "Party")
	bool RemoveActiveChar(UPARAM(ref) FString& CharName);
	/**
	* �Ѱܹ��� ĳ���Ͱ� ������Ͽ� �� �ִ��� Ȯ���Ѵ�
	* @param CharName - ĳ���� �̸�
	* @return ������Ͽ� �����ϸ� true, �ƴҽ� false ��ȯ
	*/
	UFUNCTION(BlueprintCallable, Category = "Party")
	bool IsActiveChar(UPARAM(ref) FString& CharName) const;

	/**
	* �Ѱܹ��� ĳ���͸� ������ Ž���ϴ� ĳ���ͷ� �����Ѵ�
	* @param CharName - ĳ���� �̸�
	* @return ������Ͽ� �����ϸ� true, �ƴҽ� false ��ȯ
	*/
	UFUNCTION(BlueprintCallable, Category = "Character")
	void ChangeMainChar(UPARAM(ref) FString& CharName);


	/**
	* �Ѱܹ��� ������ �ڵ带 ���� �������� ������ ��ȯ�Ѵ�
	* @param itemCode - ������ �ڵ� ( DT���� Ȯ�ΰ��� )
	* @return ���� ������ �ڵ��� ������ ��ȯ( ��ī�̺� map�� tuple�� ���۷��� )
	*/
	UFUNCTION(BlueprintCallable, Category = "Item")
	const FItemInformation& GetItemInfo(int32 itemCode) const;

	/**
	* ���� �����ϰ� �ִ� �������� ����
	* @param itemCode - ������ �ڵ�
	* @return ������ ����
	*/
	UFUNCTION(BlueprintCallable, Category = "Item")
	int32 GetItemQuantity(int32 itemCode) const;
	/**
	* ��ī�̺꿡 �����ϴ� ��� �������� �Ű������� ���� ī�װ��� ���� �з��Ͽ� ��ȯ
	* @param EItemType type - ������ Ÿ��
	* @return ������ ����
	*/
	UFUNCTION(BlueprintCallable, Category = "Item")
	TArray<FItemInformation> GetItemInfoByCategory(EItemType type);

	/**
	* ���� �����ϰ� �ִ� �������� ī�װ����� ��ȯ
	* @param type - ������ Ÿ�� ������
	* @return ������ �������̼� ����ü�� ��� �迭
	*/
	UFUNCTION(BlueprintCallable, Category = "Item")
	TArray<FItemInformation> GetCurItemInfoByCategory(EItemType type);

	//util function - uobject����static function���� �̵�
	static FString GetFStringFromEnum(FString StrEnumClass,int32 Value);

	/**
	* �������� ������ �÷��̾ ���
	* @param type - ������ Ÿ�� ������
	* @return ������ �������̼� ����ü�� ��� �迭
	*/
	UFUNCTION(BlueprintCallable)
	bool UseItem(int32 itemcode, FString TargetChar);

	/**
	* ���� ������ ������ �Ű������� ���� �����Ϳ� �ǰ��� �籸��
	* @param LoadData - �ε��� ������ ������ ��� �ν��Ͻ��� ������
	*/
	void LoadGameFromData(UGameSaver* LoadData);
protected:
	/** ���� ��θ� Map�� ��� �޼���*/
	void ConstructModelPath();
	/** ������ ������ DT���� �����Ͽ� Map�� ��� �޼���*/
	void ConstructItemInfo();

	void ConstructMonsterInfo();

	/** �ʱ�ȭ �Լ�*/
	virtual void Init() override;
private:
	/** LoadModel�� delegate�Լ� bIsLoadCompleted�� true�� �ٲ���*/
	void OnMeshLoadCompleted();
	/** �ش� �ε����� ���̺� �����Ͱ� �����ϴ��� üũ*/
	bool HasSaveData(int idx);
	/** ���� ���۽� �⺻���� ĳ���� ������ ���� ( �ε��Ҷ� �ε��� �����Ϳ� ���� ��ȯ )*/
	void ConstructDefaultCharData();

	void ConstructDefaultData();
public:
	/** LoadModels ���� �ε��� ��û���� ĳ���� �ε��� ���� �ÿ� true�� �ٲ�*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool bIsLoadCompleted;

	/** LoadModels ���� �ε��� ��û���� ĳ���� �ε��� ���� �ÿ� ����Ǵ� ��������Ʈ*/
	FMeshLoadCompleteSignature MeshLoadDelegate;
protected:
	/**ĳ�����̸��� path�� ��� �ִ� ����, �������Ʈ���� ����*/
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UDataTable* ModelPath_DT;

	/**�⺻ ĳ���� �����͸� ����ִ� ������ ���̺�*/
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UDataTable* DefaultCharData_DT;

	/**������ ������ ����ִ� ������ ���̺�*/
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UDataTable* ItemData_DT;

	/**�� ������ ����ִ� ������ ���̺�*/
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UDataTable* Enemy_DT;


	/**���� �̸��� path�� ����ִ� map container*/
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TMap<FString, FStringAssetReference> PathArchive;

	/**���ӿ� ���Ǵ� �ؽ�ó�� ��Ƴ��� ��, �����Ϳ��� �߰�*/
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TMap<FString, UTexture2D*> TextureArchive;

	/**������ UI �� ���Ǵ� ��������Ʈ���� ��Ƴ��� ��, �����Ϳ��� �߰�*/
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TMap<FString, UPaperSprite*> UISpriteArchive;

	UPROPERTY()
	/**���� �̸��� ���̷�Ż �޽� �����͸�����ִ� map container*/
	TMap<FString, USkeletalMesh*> ModelArchive;

	UPROPERTY()
	/**���� �������� ������ ĳ���� ������ ����ִ� map container*/
	TMap<FString, FCharInfo> CurCharInfo;

	UPROPERTY()
	/**������ ������ ����ִ� �����̳�*/
	TMap<FString, FEnemyInfo> EnemyInfo;

	UPROPERTY()
	/**���� �������� ������ ����(bisActive) ĳ���� �̸��� ����ִ� �迭*/
	TArray<FString> CurActiveChar;

	UPROPERTY()
	/**���� �� �����ϴ� ��� �������� ������ ����ִ� �迭*/
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


