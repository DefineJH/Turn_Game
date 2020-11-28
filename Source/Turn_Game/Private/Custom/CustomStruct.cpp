// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Custom/CustomStruct.h"

void FCharInfo::IncreaseHP(int32 Amount)
{
	int32 hp = iHP + Amount;
	iHP = (hp > iMaxHP) ? iMaxHP : hp;
}

void FCharInfo::IncreaseSP(int32 Amount)
{
	int32 sp = iSP + Amount;
	iSP = (sp > iMaxSP) ? iMaxSP : sp;
}

void FCharInfo::DecreaseHP(int32 Amount)
{
	int32 hp = iHP - Amount;
	iHP = (hp < 0) ? 0 : hp;
}

void FCharInfo::DecreaseSP(int32 Amount)
{
	int32 sp = iSP - Amount;
	iSP = (sp < 0) ? 0 : sp;
}
