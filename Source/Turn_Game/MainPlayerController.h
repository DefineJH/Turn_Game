// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TURN_GAME_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Widgets")
	TSubclassOf<class UUserWidget> WPauseMenu;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category = "Widgets")
	UUserWidget* PauseMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Widgets")
	TSubclassOf<UUserWidget> WPartyMenu;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, category = "Widgets")
	UUserWidget* PartyMenu;

	bool bPauseMenuVisibility;
	bool bPartyMenuVisibility;

	char overlayDepth = 0;
public:
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void DisplayPauseMenu();
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void DisplayPartyMenu();

	UFUNCTION(BlueprintCallable, Category = "Widget")
	void Back();
protected:
	virtual void BeginPlay() override;
private:
	void SetUIInput();
	void SetGameInput();

	void RemovePauseMenu();
	void RemovePartyMenu();
};
