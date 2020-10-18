// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SubMenuParent.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

/**
 * ������ �����ϸ� ������ ������ ��Ʈ �޴�
 * ����޴����� ������ �� ����
 */

class UUserWidget;

UCLASS()
class TURN_GAME_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<USubMenuParent> PartyMenuClass;
protected:
	USubMenuParent* PartyMenu;
protected:
	//��Ƽ�޴� ������ �ҷ��´�
	UFUNCTION(BlueprintCallable)
	void ViewPartyMenu();
};
