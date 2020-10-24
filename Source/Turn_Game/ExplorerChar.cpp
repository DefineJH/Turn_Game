// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplorerChar.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
// Sets default values
AExplorerChar::AExplorerChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(L"SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>(L"Camera");
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void AExplorerChar::BeginPlay()
{
	Super::BeginPlay();

	bUseControllerRotationYaw = false;
	SpringArm->bUsePawnControlRotation = true;

	UCharacterMovementComponent* MovementComp = Cast<UCharacterMovementComponent>(GetMovementComponent());
	if (MovementComp)
	{
		MovementComp->bUseControllerDesiredRotation = true;
		MovementComp->bOrientRotationToMovement = true;
	}
	
}

void AExplorerChar::MoveVertical(float value)
{
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRot = FRotator(0.f, Rotation.Yaw, 0.f);

	const FVector Dir = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
	AddMovementInput(Dir, value);
}

void AExplorerChar::MoveHorizontal(float value)
{
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRot = FRotator(0.f, Rotation.Yaw, 0.f);

	const FVector Dir = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);
	AddMovementInput(Dir, value);
}

// Called every frame
void AExplorerChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AExplorerChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Vertical", this, &AExplorerChar::MoveVertical);
	PlayerInputComponent->BindAxis("Horizontal", this, &AExplorerChar::MoveHorizontal);

	PlayerInputComponent->BindAxis("Turn", this, &AExplorerChar::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AExplorerChar::AddControllerPitchInput);
}

