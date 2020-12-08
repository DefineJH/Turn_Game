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
	* �Ͻ������� �޴��� �ҷ���
	*/
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void DisplayPauseMenu();
	/**
	* �Ͻ� �����޴��� ����Ʈ�� ����
	*/
	void RemovePauseMenu();

	/**
	* ���� �����޴��� ����޴��� ������� �����̸� ����޴��� ����, �ƴϸ� �����޴��� ����
	*/
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void Back();

	/**
	* �������� ������ �̷���� ����޴��� UI�� �����ؾ� �ҽ� ���
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
