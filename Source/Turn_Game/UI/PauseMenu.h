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
	bool GetIsRoot();
	void RemoveSubMenu();
	UFUNCTION(BlueprintCallable)
	void UpdateCurMenu();
protected:
	virtual bool Initialize() override;

	//��Ƽ�޴� ������ �ҷ��´�
	UFUNCTION(BlueprintCallable)
	void ViewPartyMenu();

	//��Ƽ�޴� ������ �ҷ��´�
	UFUNCTION(BlueprintCallable)
	void ViewSaveMenu();


public:
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<USubMenuParent> PartyMenuClass;
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<USubMenuParent> SaveMenuClass;
protected:
	USubMenuParent* PartyMenu;
	USubMenuParent* SaveMenu;

	USubMenuParent* CurrentMenu;
};
