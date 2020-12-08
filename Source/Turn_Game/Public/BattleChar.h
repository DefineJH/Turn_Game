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
	플레이어, 몬스터들에 iActionIndex를 넘겨줄경우, 그거에 맞는 패턴을 실행시키게함.
	*/
	UFUNCTION(BlueprintCallable, Category = "Action")
		virtual	FActionInfo PatternSetting(FUiInfo uiInfo);

public:
	//Set 함수

public:
	//Get 함수

protected:
	// 행동을 통해 값이 들어간것을 초기화시켜주기.
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
