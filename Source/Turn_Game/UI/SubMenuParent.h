// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SubMenuParent.generated.h"

/**
 * 모든 서브메뉴가 상속받는 위젯 클래스, PauseMenu서 컨테이너로 관리하며 다형성을 위해서 만듦 (constructsubwidget)
 */
UCLASS()
class TURN_GAME_API USubMenuParent : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void ConstructSubWidget();
};
