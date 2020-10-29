// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SubMenuParent.h"
#include "SubMenuParty.generated.h"

/**
 * 
 */

class UUserWidget;
class UVerticalBox;
UCLASS()
class TURN_GAME_API USubMenuParty : public USubMenuParent
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	virtual void ConstructSubWidget() override;
	virtual void UpdateSubWidget() override;
protected:
	//ĳ���� �Ѹ��� �����ϴ� ������ ���� Ŭ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite , Category = "Widget")
	TSubclassOf<UUserWidget> CharDisplayWidget;
	//ĳ���� ������� ��� ��Ƽ�ùڽ�
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta =(BindWidget))
	UVerticalBox* CharLayoutBox;
	
};
