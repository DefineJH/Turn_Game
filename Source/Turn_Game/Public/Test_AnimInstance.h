// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Test_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TURN_GAME_API UTest_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UTest_AnimInstance();
	virtual void NativeUpdateAnimation(float fDeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Pawn, Meta=(AllowPrivateAccess=true))
	float	CurrentPawnSpeed;
};
