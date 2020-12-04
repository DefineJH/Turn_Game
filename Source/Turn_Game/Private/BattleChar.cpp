// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleChar.h"
#include "../GI_Archive.h"
#include "../Public/Custom/CustomStruct.h"
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

	MeshComp->SetRelativeLocation(FVector(0.0f, 0.0f, -88.0f));		// �ݶ��̴��� ��ġ�� �޽��� ��ġ�� ���߱� ���ؼ� ĸ���� ���α��̸�ŭ ������.

	CapsuleComp->SetCapsuleHalfHeight(88.0f);	// ĸ���� ���α���?
	CapsuleComp->SetCapsuleRadius(34.0f);		// ĸ���� ���εѷ�?

	//MeshComp->SetRelativeRotation() : ī�޶��� ��ġ��°Ű���
}

// Called when the game starts or when spawned
void ABattleChar::BeginPlay()
{
	Super::BeginPlay();
	

	//UGI_Archive* Arch = Cast<UGI_Archive>(GetGameInstance());
	//if (Arch)
	//{
	//	// ������ ���, Yakumo�� �������ϰ�, 
	//	if(eType == EPlayerType::E_Enemy)
	//		SetCharMesh("Yakumo");

	//	SetCharMesh("Mia");
	//}
}

// Called every frame
void ABattleChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABattleChar::SetCharMesh(USkeletalMesh* CharMesh)
{
	if (CharMesh)
	{
		MeshComp->SetSkeletalMesh(CharMesh);
	}
}

FActionInfo ABattleChar::PatternSetting(FUiInfo uiInfo)
{
	return FActionInfo();
}

void ABattleChar::ResetActionInfo(void)
{
	m_ActionInfo.eTargetType = ETargetType::E_NONE;
	m_ActionInfo.fAtt = 0.0f;
	m_ActionInfo.fAtt = 0.0f;
	m_ActionInfo.iAnimNumber = 0;
	m_ActionInfo.iHp = 0;
	m_ActionInfo.iSp = 0;
	m_ActionInfo.iTargetIndex = 0;
}



