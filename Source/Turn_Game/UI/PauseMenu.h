// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SubMenuParent.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

/**
 * 게임을 진행하며 레벨서 나오는 루트 메뉴
 * 서브메뉴들을 관리할 수 있음
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

	//파티메뉴 생성후 불러온다
	UFUNCTION(BlueprintCallable)
	void ViewPartyMenu();

	//파티메뉴 생성후 불러온다
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
