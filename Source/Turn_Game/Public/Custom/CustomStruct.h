// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "CusomEnum.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CustomStruct.generated.h"

/**
 * 
 */
UCLASS()
class TURN_GAME_API UCustomStruct : public UObject
{
	GENERATED_BODY()
	
};

// ����ü (Struct)
// Atomic : ����ü�� �׻� �ϳ��� ������ ����ȭ(Serialize)���� �ǹ��ϰ� / BlueprintType : ����ü�� �������Ʈ���� ���� �� ������ �ǹ�.
// ����ü���� int16 (short)���� ��� �� �� ����. (������ ���� ���� ����� �׽�Ʈ�Ϸ��� �̰����� ��ġ�ٺ��� ã�Ƴ�)
// �׷��� �������� �ּҰ��� int���� ����ؾ���. ������ �𸣰���.

USTRUCT(Atomic, BlueprintType)
struct FTurnInfo								// TurnInformation, �ϸŴ������� �� ����ü
{
	GENERATED_BODY()							// �𸮾� �������ý��ۿ� �������ؼ� ���ǵǾ����.

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)		// EditAnyWhere�� �����ؾ��Ѵٰ���, �̰� �Ƹ� ����Ʈ�� ����
		float	fAtt;							// ���ݷ� (Attack / 4����Ʈ)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		float	fDef;							// ���� (Deffence / 4����Ʈ)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32	iPlayerCount;					// ���° �÷��̾����� (signed int�� / 4����Ʈ)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32	iMonsterCount;					// ���° �������� (signed int�� / 4����Ʈ)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32	iAnimNumber;					// �ִϸ��̼ǹ�ȣ (AnimationNumber / signed int�� / 4����Ʈ)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32	iSpeed;							// ��ų�� �켱������ġ (Speed / signed int�� / 4����Ʈ)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32	iSkillNumber = -1;				// � ��ų�� ����� ��ų�� ��ȣ���� (��ų�� �ƴ� ���� ����Ʈ�� -1)
		/*UPROPERTY(EditAnyWhere, BlueprintReadWrite)*/
};

USTRUCT(Atomic, BlueprintType)
struct FSkillInfo								// Skillinformation
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		float	fAtt;							// ���ݷ� (Attack / 4����Ʈ)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		float	fDef;							// ���� (Deffence / 4����Ʈ)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32	iTargetNumber;					// ���� ������ Ÿ���� ��ȣ (signed int�� / 4����Ʈ)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32	iSP;							// �Ҹ�Ǵ� SkillPoint (signed int�� / 4����Ʈ)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FName	FSkillName;						// FName�� FString�� FText�θ�, �׸��� FString ������ ��ȯ ������.	(ũ�⸦ ��)
													// ex) FName TestHUDName = FName(TEXT("ThisIsMyTestName"));
};


USTRUCT(Atomic, BlueprintType)
struct FActionInfo								// �÷��̾� Ȥ�� ���Ͱ� ������ ó���ؾ��� ������ �Ȱ��� �޾Ƽ� ���Խ�Ű�� �뵵�� ����ü
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		float	fAtt;							// ���ݷ� (Attack / 4����Ʈ)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		float	fDef;							// ���� (Deffence / 4����Ʈ)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32	iPlayerCount;					// ���° �÷��̾����� (signed int�� / 4����Ʈ)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32	iMonsterCount;					// ���° �������� (signed int�� / 4����Ʈ)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32	iAnimNumber;					// �ִϸ��̼ǹ�ȣ (AnimationNumber / signed int�� / 4����Ʈ)

		//FActionInfo������ Speed���� �ʿ䰡 ���� (�ϸŴ������� ���ǵ尪���� �켱������ ���ϴ� �뵵�θ� ����ϱ⶧��)
};


USTRUCT(Atomic, BlueprintType)
struct FPawnInfo								// �÷��̾�� ������ �⺻���� ��ġ����
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32	iHp;							// HP (signed int�� / 4����Ʈ)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32	iSp;							// SP (signed int�� / 4����Ʈ)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32	iActionNumber;					// ���������� ���� ������ ��ȣ (signed int�� / 4����Ʈ)

};

//ĳ���� �̸��� �н��� �����ϴ� ����ü, datatable�б⿡ ��� (�׷��� ���� FTableRowBase ���)
USTRUCT(Atomic, BlueprintType)
struct FModelPath : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Path;
};

USTRUCT(Atomic, BlueprintType)
struct FCharInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 iLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 iHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 iSP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 iMaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 iMaxSP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 iExp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fAtt;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fDef;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EElementalType type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsActive;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsInParty;
};

USTRUCT(Atomic, BlueprintType)
struct FItemInformation : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemCode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemDesc;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EStatusType, int32> ItemStat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanUse;
};
