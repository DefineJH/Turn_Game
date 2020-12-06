// Fill out your copyright notice in the Description page of Project Settings.


#include "Test_AnimInstance.h"

UTest_AnimInstance::UTest_AnimInstance()
{
	CurrentPawnSpeed = 0.0f;
}

void UTest_AnimInstance::NativeUpdateAnimation(float fDeltaSeconds)
{
	Super::NativeUpdateAnimation(fDeltaSeconds);

	auto Pawn = TryGetPawnOwner();	// TryGetPawnOwner() : �ִϸ��̼� �ý����� ���� �����Ҷ� ���� �� ��ü�� ��ȿ������ �����ϰ��ϴ� ���.
	if (::IsValid(Pawn))
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
	}
}
