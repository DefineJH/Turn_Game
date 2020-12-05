#pragma once
#include "GameFramework/PlayerController.h"
#include "CoreMinimal.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
class UPauseMenu;

UCLASS()
class TURN_GAME_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	/**
	* 일시정지시 메뉴를 불러옴
	*/
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void DisplayPauseMenu();
	/**
	* 일시 정지메뉴를 뷰포트서 삭제
	*/
	void RemovePauseMenu();

	/**
	* 만약 정지메뉴서 서브메뉴를 띄워놓은 상태이면 서브메뉴를 삭제, 아니면 정지메뉴를 삭제
	*/
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void Back();

	/**
	* 데이터의 갱신이 이루어져 서브메뉴의 UI를 수정해야 할시 사용
	*/
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void UpdateWidget();
protected:
	virtual void BeginPlay() override;
private:
	void SetUIInput();
	void SetGameInput();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Widgets")
	TSubclassOf<class UUserWidget> WPauseMenu;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category = "Widgets")
	UPauseMenu* PauseMenu;

};
