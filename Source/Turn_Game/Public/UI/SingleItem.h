// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "SingleItem.generated.h"
/**
 * IUserObjectListEntry - ListView의 위젯이 상속받아야 하는 인터페이스
 */


class UImage;
class UTextBlock;
class UItemDataObject;

UCLASS()
class TURN_GAME_API USingleItem : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
public:
protected:
	/**
	* 선택되었는지를 기준으로 블루프린트에서 UI애니메이션 재생하기 위해 쓰는 함수
	*/
	UFUNCTION(BlueprintNativeEvent)
	void NativeOnItemSelectionChanged(bool bIsSelected) override;
	/**
	* 리스트뷰의 아이템 구현시 UI를 위해 정보구성
	*/
	virtual void NativeOnListItemObjectSet(UObject* ItemObj) override;
protected:
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ItemImage;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemName;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemQuantity;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemDesc;

	UItemDataObject* itemData;
};
