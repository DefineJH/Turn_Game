// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleChar.h"
#include "Custom/CusomEnum.h"
#include "BattleChar_Player.generated.h"

/**
 * 
 */
UCLASS()
class TURN_GAME_API ABattleChar_Player : public ABattleChar
{
	GENERATED_BODY()

public:
	ABattleChar_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual	FActionInfo PatternSetting(FUiInfo uiInfo);

public:
	UFUNCTION(BlueprintCallable, Category = "Animation")
	EWeaponType GetWeaponType();
	UFUNCTION(BlueprintCallable, Category = "Animation")
	ESexType GetSexType();

	UFUNCTION(BlueprintCallable, Category = "Info")
	void SetCharInfo(FCharInfo Info);
public:
	UFUNCTION(BlueprintCallable, Category = "Attack")
		virtual FActionInfo Attack(FUiInfo uiInfo);

	UFUNCTION(BlueprintCallable, Category = "Guard")
		virtual void Guard();

	UFUNCTION(BlueprintCallable, Category = "Skill")
		virtual void Skill();

	UFUNCTION(BlueprintCallable, Category = "Item")
		virtual void Item();

	UFUNCTION(BlueprintCallable, Category = "Run")
		virtual void Run();

protected:
	FCharInfo m_CharInfo;


};
