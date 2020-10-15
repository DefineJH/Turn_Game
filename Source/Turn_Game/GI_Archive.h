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
	//UI���� ���� ĳ���� ����� �ٲܶ� ���
	UFUNCTION(BlueprintCallable, Category = "Generate")
	void LoadModels(TArray<FString> CharName);
	//model�� Archive�� �ִ��� �˾ƺ��� ������ optional������ ��Ƽ� ��ȯ.
	TOptional<USkeletalMesh*> QueryModel(FString name);
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
	//���� �̸��� ���̷�Ż �޽� �����͸�����ִ� map container
	TMap<FString, USkeletalMesh*> ModelArchive;

	TSharedPtr<FStreamableHandle> StreamHandle;

};
