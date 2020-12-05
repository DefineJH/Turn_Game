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
class UButton;

UCLASS()
class TURN_GAME_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	/**
	* 현재 서브메뉴가 존재하지 않고 Pause메뉴가 제일 상단인지를 반환
	*/
	bool GetIsRoot();
	void RemoveSubMenu();
	UFUNCTION(BlueprintCallable)
	void UpdateCurMenu();
	void SetFocus();
protected:
	virtual bool Initialize() override;

	//파티메뉴 생성후 불러온다
	UFUNCTION(BlueprintCallable)
	void ViewPartyMenu();

	//파티메뉴 생성후 불러온다
	UFUNCTION(BlueprintCallable)
	void ViewSaveMenu();

	//인벤토리메뉴 생성후 불러온다
	UFUNCTION(BlueprintCallable)
	void ViewInvenMenu();

private:
	void DisableFocus();

public:
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<USubMenuParent> PartyMenuClass;
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<USubMenuParent> SaveMenuClass;
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<USubMenuParent> InvenMenuClass;
protected:
	USubMenuParent* PartyMenu;
	USubMenuParent* SaveMenu;
	USubMenuParent* InvenMenu;

	USubMenuParent* CurrentMenu;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* PartyBtn;
};
