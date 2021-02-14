// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Custom/CustomStruct.h"

void FThingsInfo::IncreaseHP(int32 Amount)
{
	int32 hp = iHP + Amount;
	iHP = (hp > iMaxHP) ? iMaxHP : hp;
}

void FThingsInfo::IncreaseSP(int32 Amount)
{
	int32 sp = iSP + Amount;
	iSP = (sp > iMaxSP) ? iMaxSP : sp;
}

void FThingsInfo::DecreaseHP(int32 Amount)
{
	int32 hp = iHP - Amount;
	iHP = (hp < 0) ? 0 : hp;
}

void FThingsInfo::DecreaseSP(int32 Amount)
{
	int32 sp = iSP - Amount;
	iSP = (sp < 0) ? 0 : sp;
}



