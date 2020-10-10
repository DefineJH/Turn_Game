// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CusomEnum.generated.h"

/**
 * 
 */
UCLASS()
class TURN_GAME_API UCusomEnum : public UObject
{
	GENERATED_BODY()
	
};


// 열거형 (Enum)
// 언리얼 열거형을 만들때 반드시 일반적인 enum이 아닌 enum class로 만들어야 한다는 점.
// enum class로 만들지 않고 일반적인 enum으로 만들어서 UENUM() 매크로를 붙이고 컴파일을 하면 에러가 발생.
// 또한 UENUM은 uint8만을 지원하기 때문에 이부분도 빠뜨리지 않아야 함.

// ps. enum와 enum class의 차이점이 적힌 블로그 보고 어떤걸 쓰기원하는지 판단해줘 https://unikys.tistory.com/376

UENUM(BlueprintType)
enum class EActionState : uint8
{
	E_Attack 	UMETA(DisplayName = "Attack"),
	E_Guard		UMETA(DisplayName = "Guard"),
	E_Skill		UMETA(DisplayName = "Skill"),
	E_Item		UMETA(DisplayName = "Item")
};

UENUM(BlueprintType)
enum class ETurnMgrState : uint8
{
	E_WaitForCommand	UMETA(DisplayName = "WaitForCommand"),
	E_Execute			UMETA(DisplayName = "Execute")
};
