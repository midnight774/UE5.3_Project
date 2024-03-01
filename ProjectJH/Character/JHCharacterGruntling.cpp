// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/JHCharacterGruntling.h"
#include "Animation/AnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AI/JHGruntlingAIController.h"
#include "Animation/JHSpiderAnimInstance.h"
#include "Animation/AnimMontage.h"
#include "CharacterStat/JHCharacterStatComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/AssetManager.h"
#include "Actor/JHActorProjectile.h"
#include "Collision/JHCollision.h"

AJHCharacterGruntling::AJHCharacterGruntling()
{
	CharacterName = TEXT("Gruntling");
	ComboCountMax = 3;

	FString MeshFileRef = TEXT("/Script/Engine.SkeletalMesh'/Game/InfinityBladeAdversaries/Enemy/Enemy_Master_Grunt/SK_Master_Grunt.SK_Master_Grunt'");
	EnemyMeshPath = FSoftObjectPath(MeshFileRef);

	//Capsule
	GetCapsuleComponent()->InitCapsuleSize(50.0f, 50.0f);

	//Mesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -30.0f), FRotator(0.0f, -90.0f, 0.0f));

	//Weapon Mesh
	FString WeaponRef = TEXT("/Script/Engine.StaticMesh'/Game/InfinityBladeAdversaries/Enemy/Enemy_Gruntling_Weapons/Meshes/SM_Gruntling_Torch_Internal.SM_Gruntling_Torch_Internal'");
	WeaponMeshPath = FSoftObjectPath(WeaponRef);

	//Animation
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UJHAnimInstance> GruntlingAnimInstRef(TEXT("/Game/ProectJH/Animation/Enemy/Gruntling/ABP_Gruntling_Animation.ABP_Gruntling_Animation_C"));

	if (GruntlingAnimInstRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(GruntlingAnimInstRef.Class);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> GruntlingAtkMontageRefA(TEXT("/Script/Engine.AnimMontage'/Game/ProectJH/Animation/Enemy/Gruntling/AM_Gruntling_Attack_A.AM_Gruntling_Attack_A'"));

	if (GruntlingAtkMontageRefA.Object)
	{
		ArrAttackMontage.Add(GruntlingAtkMontageRefA.Object);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> GruntlingAtkMontageBRef(TEXT("/Script/Engine.AnimMontage'/Game/ProectJH/Animation/Enemy/Gruntling/AM_Gruntling_Attack_B.AM_Gruntling_Attack_B'"));

	if (GruntlingAtkMontageBRef.Object)
	{
		ArrAttackMontage.Add(GruntlingAtkMontageBRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> GruntlingAtkMontageCRef(TEXT("/Script/Engine.AnimMontage'/Game/ProectJH/Animation/Enemy/Gruntling/AM_Gruntling_Attack_C.AM_Gruntling_Attack_C'"));

	if (GruntlingAtkMontageCRef.Object)
	{
		ArrAttackMontage.Add(GruntlingAtkMontageCRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackRangeMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/ProectJH/Animation/Enemy/Gruntling/AM_Gruntling_Attack_Range.AM_Gruntling_Attack_Range'"));

	if (AttackRangeMontageRef.Object)
	{
		AttackRangeMontage = AttackRangeMontageRef.Object;
	}


	static ConstructorHelpers::FObjectFinder<UAnimMontage> GruntlingDeadMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/ProectJH/Animation/Enemy/Gruntling/AM_Gruntling_Dead.AM_Gruntling_Dead'"));

	if (GruntlingDeadMontageRef.Object)
	{
		DeadMontage = GruntlingDeadMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> GruntlingRangeParticleRef(TEXT("/Script/Engine.ParticleSystem'/Game/ProectJH/Effect/Gruntling/P_Projectile_MGrunt.P_Projectile_MGrunt'"));

	if (GruntlingRangeParticleRef.Object)
	{
		AttackRangeBodyParticle = GruntlingRangeParticleRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> GruntlingRangeHitParticleRef(TEXT("/Script/Engine.ParticleSystem'/Game/ProectJH/Effect/Gruntling/P_ProjectileLob_BreakUp_02.P_ProjectileLob_BreakUp_02'"));

	if (GruntlingRangeHitParticleRef.Object)
	{
		AttackRangeHitParticle = GruntlingRangeHitParticleRef.Object;
	}

	AIControllerClass = AJHGruntlingAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AJHCharacterGruntling::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	FSimpleDelegate LoadDelegate = FStreamableDelegate::CreateUObject(this, &AJHCharacterGruntling::IsCompletedLoadWeaponMesh);
	WeaponMeshHandle = UAssetManager::GetStreamableManager().RequestAsyncLoad(WeaponMeshPath, LoadDelegate);
}

void AJHCharacterGruntling::BeginPlay()
{
	Super::BeginPlay();
	NextComboEnableTime = 1.0f;
	ComboTimeMax = 2.0f;

	PatrolDistance = 500.0f;
	DetectDistance = 1500.0f;
	AttackDistance = 150.0f;
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -50.0f), FRotator(0.0f, -90.0f, 0.0f));
	RootComponent->SetWorldScale3D(FVector(1.5f, 1.5f, 1.5f));
}

void AJHCharacterGruntling::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AJHGruntlingAIController* AIController = Cast<AJHGruntlingAIController>(GetController());

	if (AIController)
	{
		LookTargetPos = AIController->GetTargetPos();
	}

}

void AJHCharacterGruntling::ProcessComboAttack()
{
	Super::ProcessComboAttack();
}

void AJHCharacterGruntling::AttackFinish()
{
	Super::AttackFinish();
}

void AJHCharacterGruntling::SetDead()
{
	Super::SetDead();
}

float AJHCharacterGruntling::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Damage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	return Damage;
}

void AJHCharacterGruntling::IsCompletedLoadWeaponMesh()
{
	if (WeaponMeshHandle.IsValid())
	{
		UStaticMeshComponent* LeftWeapon = NewObject<UStaticMeshComponent>(this);
		LeftWeapon->SetStaticMesh(Cast<UStaticMesh>(WeaponMeshHandle->GetLoadedAsset()));
		UStaticMeshComponent* RightWeapon = NewObject<UStaticMeshComponent>(this);
		RightWeapon->SetStaticMesh(Cast<UStaticMesh>(WeaponMeshHandle->GetLoadedAsset()));

		LeftWeapon->SetupAttachment(GetMesh(), TEXT("b_MF_Weapon_L"));
		RightWeapon->SetupAttachment(GetMesh(), TEXT("b_MF_Weapon_R"));

		LeftWeapon->RegisterComponent();
		RightWeapon->RegisterComponent();

		LeftWeapon->SetWorldScale3D(FVector(3.0f, 3.0f, 3.0f));
		LeftWeapon->SetRelativeLocation(FVector(15.0f, 1.0f, 0.0f));
		LeftWeapon->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));

		RightWeapon->SetWorldScale3D(FVector(3.0f, 3.0f, 3.0f));
		RightWeapon->SetRelativeLocation(FVector(15.0f, 1.0f, 0.0f));
		RightWeapon->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));

		WeaponMeshHandle->ReleaseHandle();
	}
}

AJHActorProjectile* AJHCharacterGruntling::SpawnProjectile(const FVector& MoveDir, const FVector& SpawnPos, float MoveSpeed, float MoveTime)
{
	AJHActorProjectile* Projectile = GetWorld()->SpawnActor<AJHActorProjectile>();

	FVector PlayerPos = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FVector Dir = PlayerPos - SpawnPos;
	Dir.Normalize();

	Projectile->SetMoveDir(Dir);
	Projectile->SetMoveSpeed(MoveSpeed);
	Projectile->SetMoveTime(MoveTime);
	Projectile->SetActorLocation(SpawnPos);

	Projectile->SetBodyParticle(AttackRangeBodyParticle);
	Projectile->SetHitParticle(AttackRangeHitParticle);

	return Projectile;
}

void AJHCharacterGruntling::StartFireMontage()
{
	if (AttackRangeMontage)
	{
		UJHAnimInstance* AnimInst = Cast<UJHAnimInstance>(GetMesh()->GetAnimInstance());

		if (AnimInst)
		{
			AnimInst->Montage_Play(AttackRangeMontage);
		}
	}
}

void AJHCharacterGruntling::AdjustFirePos()
{
	IsTargetLooking = true;
}

void AJHCharacterGruntling::FireProjectile()
{
	IsTargetLooking = false;
	FVector MuzzlePos = GetMesh()->GetSocketLocation(TEXT("b_Muzzle"));
	AJHActorProjectile* Projectile = SpawnProjectile(GetActorForwardVector(), MuzzlePos, 4000.0f, 0.5f);
	Projectile->SetCollisionProfile(COL_PROFILE_TRIGGER);
}
