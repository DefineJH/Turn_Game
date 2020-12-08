// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleChar_Player.h"

ABattleChar_Player::ABattleChar_Player()
{
	m_eType = EPlayerType::E_Player;
}

void ABattleChar_Player::BeginPlay()
{
	Super::BeginPlay();
}

FActionInfo ABattleChar_Player::PatternSetting(FUiInfo uiInfo)
{
	switch (uiInfo.iActionIndex)
	{
		ResetActionInfo();	// 한번 초기화 해준 후 actionInfo의 값을 적용.
	case 0 :
		return Attack(uiInfo);
	case 1:
		Guard();
		break;
	case 2:
		Skill();
		break;
	case 3:
		Item();
		break;
	case 4:
		Run();
		break;
	default:
		break;
	}
	return FActionInfo();
}

EWeaponType ABattleChar_Player::GetWeaponType()
{
	return eWeaponType;
}

FActionInfo ABattleChar_Player::Attack(FUiInfo uiInfo)
{
	m_ActionInfo.eTargetType = uiInfo.eTargetType;
	m_ActionInfo.iTargetIndex = uiInfo.iTargetIndex;
	m_ActionInfo.fAtt = 3;
	m_ActionInfo.fDef = 0;
	m_ActionInfo.iAnimNumber = 1; // 1이 공격이라고 가정
	m_ActionInfo.iHp = 0;
	m_ActionInfo.iSp = 0;

	return m_ActionInfo;
}

void ABattleChar_Player::Guard(void)
{
}

void ABattleChar_Player::Skill(void)
{
}

void ABattleChar_Player::Item(void)
{
}

void ABattleChar_Player::Run(void)
{
}
