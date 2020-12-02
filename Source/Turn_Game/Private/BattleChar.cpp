// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleChar.h"
#include "../GI_Archive.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABattleChar::ABattleChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));

	RootComponent = CapsuleComp;
	MeshComp->SetupAttachment(CapsuleComp);	// ()�ȿ��ִ� Component�� �θ�� ����� �Լ�

	CapsuleComp->SetCapsuleHalfHeight(88.0f);	// ĸ���� ���α���?
	CapsuleComp->SetCapsuleRadius(34.0f);		// ĸ���� ���εѷ�?

	//MeshComp->SetRelativeRotation() : ī�޶��� ��ġ��°Ű���
}

// Called when the game starts or when spawned
void ABattleChar::BeginPlay()
{
	Super::BeginPlay();
	

	UGI_Archive* Arch = Cast<UGI_Archive>(GetGameInstance());
	if (Arch)
	{
		SetCharMesh("Mia");
	}
}

// Called every frame
void ABattleChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABattleChar::SetCharMesh(FString CharName)
{
	UGI_Archive* Arch = Cast<UGI_Archive>(GetGameInstance());
	if (Arch)
	{
		auto model = Arch->QueryModel(CharName);
		if (model.IsSet())
		{
			MeshComp->SetSkeletalMesh(model.GetValue());
			UE_LOG(LogTemp, Warning, L"MeshSet");
		}
		else
		{
			Arch->MeshLoadDelegate.BindUFunction(this, L"SetCharMesh");
			UE_LOG(LogTemp, Warning, L"MeshSetAsync");
		}
	}
}


