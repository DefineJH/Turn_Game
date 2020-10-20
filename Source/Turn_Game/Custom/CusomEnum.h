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


// ������ (Enum)
// �𸮾� �������� ���鶧 �ݵ�� �Ϲ����� enum�� �ƴ� enum class�� ������ �Ѵٴ� ��.
// enum class�� ������ �ʰ� �Ϲ����� enum���� ���� UENUM() ��ũ�θ� ���̰� �������� �ϸ� ������ �߻�.
// ���� UENUM�� uint8���� �����ϱ� ������ �̺κе� ���߸��� �ʾƾ� ��.

// ps. enum�� enum class�� �������� ���� ��α� ���� ��� ������ϴ��� �Ǵ����� https://unikys.tistory.com/376

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

UENUM(BlueprintType)
enum class EElementalType : uint8
{
	E_Fire			UMETA(DisplayName = "Fire"),
	E_Ice			UMETA(DisplayName = "Ice"),
	E_Wind			UMETA(DisplayName = "Wind"),
	E_Electric		UMETA(DisplayName = "Electric"),
	E_Void			UMETA(DisplayName = "Void"),
	E_Light			UMETA(DisplayName = "Light"),
	E_Dark			UMETA(DisplayName = "Dark"),
	E_MAX			UMETA(DisplayName = "MAX"),
};