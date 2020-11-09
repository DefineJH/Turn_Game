// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSaver.h"

FCharInfo UGameSaver::GetCharInfo(FString name) const
{
	for (const FCharInfo& info : CharInfos)
	{
		if (info.Name == name)
			return info;
	}
	return FCharInfo{};
}
