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
class UButton;

UCLASS()
class TURN_GAME_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	/**
	* ���� ����޴��� �������� �ʰ� Pause�޴��� ���� ��������� ��ȯ
	*/
	bool GetIsRoot();
	void RemoveSubMenu();
	UFUNCTION(BlueprintCallable)
	void UpdateCurMenu();
	void SetFocus();
protected:
	virtual bool Initialize() override;

	//��Ƽ�޴� ������ �ҷ��´�
	UFUNCTION(BlueprintCallable)
	void ViewPartyMenu();

	//��Ƽ�޴� ������ �ҷ��´�
	UFUNCTION(BlueprintCallable)
	void ViewSaveMenu();

	//�κ��丮�޴� ������ �ҷ��´�
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
