// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleChar_Player.h"

ABattleChar_Player::ABattleChar_Player()
{
	eType = EPlayerType::E_Player;
}

void ABattleChar_Player::BeginPlay()
{
	Super::BeginPlay();
}