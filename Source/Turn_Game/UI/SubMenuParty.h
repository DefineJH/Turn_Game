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
	//캐릭터 한명을 설명하는 위젯에 대한 클래스
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite , Category = "Widget")
	TSubclassOf<UUserWidget> CharDisplayWidget;
	//캐릭터 설명들을 담는 버티컬박스
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta =(BindWidget))
	UVerticalBox* CharLayoutBox;
	
};
