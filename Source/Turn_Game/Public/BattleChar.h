// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "../Public/Custom/CustomStruct.h"
#include "BattleChar.generated.h"

class USkeletalMeshComponent;
class UCapsuleComponent;
struct FCharInfo;

UENUM(BlueprintType)
enum class EPlayerType : uint8
{
	E_None		UMETA(DisplayName = "None"),
	E_Player	UMETA(DisplayName = "Player"),
	E_Enemy		UMETA(DisplayName = "Enemy")
};


UCLASS()
class TURN_GAME_API ABattleChar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABattleChar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Mesh")
		void SetCharMesh(USkeletalMesh* CharMesh);

public:
	/*
	�÷��̾�, ���͵鿡 iActionIndex�� �Ѱ��ٰ��, �װſ� �´� ������ �����Ű����.
	*/
	UFUNCTION(BlueprintCallable, Category = "Action")
		virtual	FActionInfo PatternSetting(FUiInfo uiInfo);

public:
	//Set �Լ�

public:
	//Get �Լ�

protected:
	// �ൿ�� ���� ���� ������ �ʱ�ȭ�����ֱ�.
	void ResetActionInfo(void);

protected:
	EPlayerType m_eType;
	FActionInfo m_ActionInfo;
public:
	UPROPERTY(BlueprintReadWrite, VisibleAnyWhere, Category = "Collision")
		UCapsuleComponent*		CapsuleComp;

	UPROPERTY(BlueprintReadWrite, VisibleAnyWhere, Category = "Mesh")
		USkeletalMeshComponent*	MeshComp;

};
