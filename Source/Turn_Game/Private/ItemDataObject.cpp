// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDataObject.h"

const FItemInformation& UItemDataObject::GetInfo() const
{
	return info;
}

void UItemDataObject::SetInfo(FItemInformation inInfo)
{
	this->info = inInfo;
}
