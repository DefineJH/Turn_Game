// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SubMenuParent.generated.h"

/**
 * ��� ����޴��� ��ӹ޴� ���� Ŭ����, PauseMenu�� �����̳ʷ� �����ϸ� �������� ���ؼ� ���� (constructsubwidget)
 */
UCLASS()
class TURN_GAME_API USubMenuParent : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void ConstructSubWidget();
};
