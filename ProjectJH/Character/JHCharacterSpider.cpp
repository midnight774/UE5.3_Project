// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/JHCharacterSpider.h"
#include "Animation/AnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AI/JHAIController.h"
#include "Animation/JHSpiderAnimInstance.h"
#include "Animation/AnimMontage.h"
#include "CharacterStat/JHCharacterStatComponent.h"
#include "LandscapeInfo.h"
#include "LandscapeDataAccess.h"
#include "LandscapeProxy.h"
#include "LandscapeComponent.h"
#include "Kismet/GameplayStatics.h"

AJHCharacterSpider::AJHCharacterSpider()
{
	CharacterName = TEXT("Spider");
	ComboCountMax = 1;

	FString MeshFileRef = TEXT("/Script/Engine.SkeletalMesh'/Game/InfinityBladeAdversaries/Enemy/Enemy_Creature_Spider/SK_EXO_Creature_Spider02.SK_EXO_Creature_Spider02'");
	EnemyMeshPath = FSoftObjectPath(MeshFileRef);

	//Capsule
	GetCapsuleComponent()->InitCapsuleSize(50.0f, 50.0f);

	//Mesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -48.0f), FRotator(0.0f, -90.0f, 0.0f));

	//Animation
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UJHSpiderAnimInstance> SpiderAnimInstRef(TEXT("/Game/ProectJH/Animation/Enemy/Spider/ABP_Spider_Animation.ABP_Spider_Animation_C"));

	if (SpiderAnimInstRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(SpiderAnimInstRef.Class);
	}
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SpiderAtkMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/ProectJH/Animation/Enemy/Spider/AM_Spider_Attack.AM_Spider_Attack'"));

	if (SpiderAtkMontageRef.Object)
	{
		ArrAttackMontage.Add(SpiderAtkMontageRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> SpiderAtkEndMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/ProectJH/Animation/Enemy/Spider/AM_Spider_AttackEnd.AM_Spider_AttackEnd'"));

	if (SpiderAtkEndMontageRef.Object)
	{
		AttackEndMontage = SpiderAtkEndMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeadMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/ProectJH/Animation/Enemy/Spider/AM_Spider_Dead.AM_Spider_Dead'"));

	if (DeadMontageRef.Object)
	{
		DeadMontage = DeadMontageRef.Object;
	}

	AIControllerClass = AJHAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AJHCharacterSpider::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AJHCharacterSpider::BeginPlay()
{
	Super::BeginPlay();

	PatrolDistance = 500.0f;
	DetectDistance = 1000.0f;
	AttackDistance = 300.0f;
}

void AJHCharacterSpider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ComputeInclineDegree();

}

void AJHCharacterSpider::ProcessComboAttack()
{
	Super::ProcessComboAttack();
}

void AJHCharacterSpider::AttackFinish()
{
	Super::AttackFinish();
}

void AJHCharacterSpider::SetDead()
{
	Super::SetDead();
}

float AJHCharacterSpider::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Damage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	return Damage;
}

void AJHCharacterSpider::ComputeInclineDegree()
{ 
	ALandscapeProxy* Landscape = Cast<ALandscapeProxy>(UGameplayStatics::GetActorOfClass(GetWorld(), ALandscapeProxy::StaticClass()));

	if (!Landscape)
		return;

	ULandscapeComponent* LandscapeComp = Landscape->GetComponentByClass<ULandscapeComponent>();
	if (!LandscapeComp)
		return;

	if (LandscapeComp)
	{
		// LandscapeInfo를 가져옵니다.
		ULandscapeInfo* LandscapeInfo = LandscapeComp->GetLandscapeInfo();

		if (LandscapeInfo)
		{
			// 기울기 정보 계산

			float Radius = GetCapsuleComponent()->GetScaledCapsuleRadius();
			FVector Location = GetActorLocation();
			FVector ForwardLocation = Location + GetActorForwardVector() * Radius;
			FVector RightLocation = Location + GetActorRightVector() * Radius;

			float Height, ForwardHeight, RightHeight;
			FVector TargetDir;
			FRotator TargetRot;

			Height = LandscapeInfo->GetLandscapeProxy()->GetHeightAtLocation(Location).GetValue();
			ForwardHeight = LandscapeInfo->GetLandscapeProxy()->GetHeightAtLocation(ForwardLocation).GetValue();
			RightHeight = LandscapeInfo->GetLandscapeProxy()->GetHeightAtLocation(RightLocation).GetValue();

			Location.Z = Height;
			ForwardLocation.Z = ForwardHeight;
			RightLocation.Z = RightHeight;

			FVector FrontDir = ForwardLocation - Location;
			FrontDir.Normalize();
			FVector RightDir = RightLocation - Location;
			RightDir.Normalize();

			TargetRot = FRotationMatrix::MakeFromXY(FrontDir, RightDir).Rotator();

			SetActorRotation(FMath::RInterpTo(GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 90.0f));

		}
	}
}
