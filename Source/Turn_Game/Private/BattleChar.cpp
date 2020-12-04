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
	MeshComp->SetupAttachment(CapsuleComp);	// ()안에있는 Component를 부모로 만드는 함수

	MeshComp->SetRelativeLocation(FVector(0.0f, 0.0f, -88.0f));		// 콜라이더의 위치와 메쉬의 위치를 맞추기 위해서 캡슐의 세로길이만큼 내려줌.

	CapsuleComp->SetCapsuleHalfHeight(88.0f);	// 캡슐의 세로길이?
	CapsuleComp->SetCapsuleRadius(34.0f);		// 캡슐의 가로둘레?

	//MeshComp->SetRelativeRotation() : 카메라의 위치잡는거같음
}

// Called when the game starts or when spawned
void ABattleChar::BeginPlay()
{
	Super::BeginPlay();
	

	//UGI_Archive* Arch = Cast<UGI_Archive>(GetGameInstance());
	//if (Arch)
	//{
	//	// 몬스터일 경우, Yakumo를 입히게하고, 
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



