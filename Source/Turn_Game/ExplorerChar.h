// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ExplorerChar.generated.h"


class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TURN_GAME_API AExplorerChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AExplorerChar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveVertical(float value);
	void MoveHorizontal(float value);

	void SetCharMesh(FString Name);

	UFUNCTION()
	void SetCharMesh_Async(const TArray<FString>& Name);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	UPROPERTY(VisibleAnywhere , Category="Camera")
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	UCameraComponent* Camera;

	FString CharName;
};
