// Fill out your copyright notice in the Description page of Project Settings.


#include "Test_AnimInstance.h"

UTest_AnimInstance::UTest_AnimInstance()
{
	CurrentPawnSpeed = 0.0f;
}

void UTest_AnimInstance::NativeUpdateAnimation(float fDeltaSeconds)
{
	Super::NativeUpdateAnimation(fDeltaSeconds);

	auto Pawn = TryGetPawnOwner();	// TryGetPawnOwner() : 애니메이션 시스템이 폰에 접근할때 먼저 폰 객체가 유효한지를 점검하게하는 명령.
	if (::IsValid(Pawn))
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
	}
}
