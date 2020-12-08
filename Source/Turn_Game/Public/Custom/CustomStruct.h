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

// 구조체 (Struct)
// Atomic : 구조체가 항상 하나의 단위로 직렬화(Serialize)됨을 의미하고 / BlueprintType : 구조체가 블루프린트에서 사용될 수 있음을 의미.
// 구조체에선 int16 (short)형을 사용 할 수 없다. (오류가 나는 곳이 어딘지 테스트하려고 이것저것 고치다보니 찾아냄)
// 그래서 정수형의 최소값은 int형을 사용해야함. 이유는 모르겠음.

USTRUCT(Atomic, BlueprintType)
struct FTurnInfo								// TurnInformation, 턴매니저에게 들어갈 구조체
{
	GENERATED_BODY()							// 언리얼에 가비지시스템에 들어가기위해선 정의되어야함.

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)		// EditAnyWhere로 설정해야한다고함, 이게 아마 디폴트로 추정
		float	fAtt;							// 공격력 (Attack / 4바이트)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		float	fDef;							// 방어력 (Deffence / 4바이트)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32	iPlayerCount;					// 몇번째 플레이어인지 (signed int형 / 4바이트)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32	iMonsterCount;					// 몇번째 몬스터인지 (signed int형 / 4바이트)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32	iAnimNumber;					// 애니메이션번호 (AnimationNumber / signed int형 / 4바이트)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32	iSpeed;							// 스킬의 우선순위수치 (Speed / signed int형 / 4바이트)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32	iSkillNumber = -1;				// 어떤 스킬을 썼는지 스킬의 번호저장 (스킬이 아닐 경우는 디폴트값 -1)
		/*UPROPERTY(EditAnyWhere, BlueprintReadWrite)*/
};

USTRUCT(Atomic, BlueprintType)
struct FSkillInfo								// Skillinformation
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		float	fAtt;							// 공격력 (Attack / 4바이트)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		float	fDef;							// 방어력 (Deffence / 4바이트)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32	iTargetNumber;					// 고유 지정된 타겟의 번호 (signed int형 / 4바이트)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32	iSP;							// 소모되는 SkillPoint (signed int형 / 4바이트)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		FName	FSkillName;						// FName은 FString과 FText로만, 그리고 FString 에서만 변환 가능함.	(크기를 모름)
													// ex) FName TestHUDName = FName(TEXT("ThisIsMyTestName"));
};


USTRUCT(Atomic, BlueprintType)
struct FActionInfo								// 플레이어 혹은 몬스터가 실제로 처리해야할 내용을 똑같이 받아서 대입시키는 용도의 구조체
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		float	fAtt;							// 공격력 (Attack / 4바이트)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		float	fDef;							// 방어력 (Deffence / 4바이트)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32	iTargetIndex;					// 몇번째 위치하는 타겟인지 (signed int형 / 4바이트)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32	iAnimNumber;					// 애니메이션번호 (AnimationNumber / signed int형 / 4바이트)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32	iHp;							// 스킬 혹은 아이템으로 인한 회복 or 감소 될 HP량
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32	iSp;							// 스킬 혹은 아이템으로 인한 회복 or 감소 될 SP량
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		ETargetType eTargetType = ETargetType::E_NONE;				// 스킬 혹은 아이템이 대상이 될 타겟의 종류

	//FActionInfo에서는 Speed값이 필요가 없음 (턴매니저에서 스피드값으로 우선순위를 정하는 용도로만 사용하기때문)
};


// Ui에서 클릭하여 나올 모든 정보의 종류의 값들
USTRUCT(Atomic, BlueprintType)
struct FUiInfo								
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32	iPlayerIndex;					// 현재 UI의 주인이 되고있는 플레이어가 몇번째의 플레이어인지 알기위함.
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32	iActionIndex;					// 현재 선택당한 행동이 어떤것인지 (ex / Attack, Guard, Skill, ..)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32	iTargetIndex;					// 몇번째에 있는 타겟인지
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32	iItemCode = -1;					// 사용할 아이템의 코드
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32	iSkillIndex = -1;				// 몇번째 스킬인지
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ETargetType	eTargetType = ETargetType::E_NONE;				// 스킬의 대상이 몬스터, 플레이어 중 누구인지

	// -1 : 사용하지않을 때의 디폴트값으로 예외처리를 하기위함.
};

USTRUCT(Atomic, BlueprintType)
struct FPawnInfo								// 플레이어와 몬스터의 기본적인 수치값들
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32	iHp;							// HP (signed int형 / 4바이트)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32	iSp;							// SP (signed int형 / 4바이트)
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		int32	iActionNumber;					// 전투에서의 고유 지정될 번호 (signed int형 / 4바이트)

};

//캐릭터 이름과 패스를 저장하는 구조체, datatable읽기에 사용 (그러기 위해 FTableRowBase 상속)
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
	void IncreaseHP(int32 Amount);
	void IncreaseSP(int32 Amount);
	void DecreaseHP(int32 Amount);
	void DecreaseSP(int32 Amount);
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
