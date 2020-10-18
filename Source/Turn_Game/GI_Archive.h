// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Misc/Optional.h"
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
UCLASS()
class TURN_GAME_API UGI_Archive : public UGameInstance
{
	GENERATED_BODY()
public:
	//UI���� ���� ĳ���� ����� �ٲܶ� ���
	UFUNCTION(BlueprintCallable, Category = "Generate")
	void LoadModels(TArray<FString> CharName);
	//model�� Archive�� �ִ��� �˾ƺ��� ������ optional������ ��Ƽ� ��ȯ.
	TOptional<USkeletalMesh*> QueryModel(FString name);
	//��Ƽ UI �����ϱ� ���� ĳ������ ���� �����ϴ� �޼���
	TArray<FCharInfo> GetCharInfo() const;

	UTexture2D* GetTextureFromName(FString& name) const;
protected:
	//ModelPath_DT�� ���� ��� ���� stringpath�� ����
	void ConstructModelPath();
	//�ʱ�ȭ �Լ�
	virtual void Init() override;
private:
	//LoadModel�� delegate�Լ� bIsLoadCompleted�� true�� �ٲ���
	void OnLoadCompleted();
public:
	//�о �� �ְ� true�� �س���, ���� ��û���� ĳ���� �ε��� ���� �ÿ� true�� �ٲ�
	//ĳ���͸� �ٲ��� �ʰ� ���Խÿ��� true�����ϴϱ� �̰ź��� ���� ����� �԰���
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool bIsLoadCompleted;
protected:
	//ĳ�����̸��� path�� ��� �ִ� ����, �������Ʈ���� ����
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UDataTable* ModelPath_DT;
	//���� �̸��� path�� ����ִ� map container
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TMap<FString, FStringAssetReference> PathArchive;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TMap<FString, UTexture2D*> UICharImgArchive;
	//���� �̸��� ���̷�Ż �޽� �����͸�����ִ� map container
	TMap<FString, USkeletalMesh*> ModelArchive;

	TArray<FCharInfo> CharInfo;

private:
	TSharedPtr<FStreamableHandle> StreamHandle;

};
