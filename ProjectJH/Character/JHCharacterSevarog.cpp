// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/JHCharacterSevarog.h"
#include "Animation/AnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AI/JHSevarogAIController.h"
#include "Animation/JHSpiderAnimInstance.h"
#include "Animation/AnimMontage.h"
#include "CharacterStat/JHCharacterStatComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/AssetManager.h"
#include "Actor/JHActorProjectile.h"
#include "Actor/JHStormActor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Actor/JHActorProjectile.h"
#include "Collision/JHCollision.h"
#include "NavigationSystem.h"
#include "UI/JHBossWidget.h"
#include "Player/JHPlayerController.h"

AJHCharacterSevarog::AJHCharacterSevarog()
{
	CharacterName = TEXT("Sevarog");
	ComboCountMax = 3;

	AutoActivateAI = false;
	bDissolveEnable = false;

	FString MeshFileRef = TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonSevarog/Characters/Heroes/Sevarog/Skins/Tier_1/Sevarog_Chronos/Meshes/SevarogChronos.SevarogChronos'");
	EnemyMeshPath = FSoftObjectPath(MeshFileRef);

	//Capsule
	GetCapsuleComponent()->InitCapsuleSize(100.0f, 300.0f);

	//Mesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -282.0f), FRotator(0.0f, -90.0f, 0.0f));

	//Animation
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UJHAnimInstance> SevarogAnimInstRef(TEXT("/Game/ParagonSevarog/Characters/Heroes/Sevarog/Sevarog_AnimBlueprint.Sevarog_AnimBlueprint_C"));

	if (SevarogAnimInstRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(SevarogAnimInstRef.Class);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> SevarogAtkMontageRefA(TEXT("/Script/Engine.AnimMontage'/Game/ProectJH/Animation/Enemy/Sevarog/AM_Swing1_Medium.AM_Swing1_Medium'"));

	if (SevarogAtkMontageRefA.Object)
	{
		ArrAttackMontage.Add(SevarogAtkMontageRefA.Object);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> SevarogAtkMontageRefB(TEXT("/Script/Engine.AnimMontage'/Game/ProectJH/Animation/Enemy/Sevarog/AM_Swing2_Medium.AM_Swing2_Medium'"));

	if (SevarogAtkMontageRefB.Object)
	{
		ArrAttackMontage.Add(SevarogAtkMontageRefB.Object);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> SevarogAtkMontageRefC(TEXT("/Script/Engine.AnimMontage'/Game/ProectJH/Animation/Enemy/Sevarog/AM_Swing3_Medium.AM_Swing3_Medium'"));

	if (SevarogAtkMontageRefC.Object)
	{
		ArrAttackMontage.Add(SevarogAtkMontageRefC.Object);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> SevarogCastMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/ProectJH/Animation/Enemy/Sevarog/AM_CastStart.AM_CastStart'"));

	if (SevarogCastMontageRef.Object)
	{
		CastMontage = (SevarogCastMontageRef.Object);
	}

	FSkillMontages SkillMontage_1;
	SkillMontage_1.CurrentMontageIdx = 0;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> SevarogSkillAMRef1_1(TEXT("/Script/Engine.AnimMontage'/Game/ProectJH/Animation/Enemy/Sevarog/AM_SiphonStart.AM_SiphonStart'"));

	if (SevarogSkillAMRef1_1.Object)
	{
		SkillMontage_1.SkillMontages.Add(SevarogSkillAMRef1_1.Object);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> SevarogSkillAMRef1_2(TEXT("/Script/Engine.AnimMontage'/Game/ProectJH/Animation/Enemy/Sevarog/AM_SoulSiphon.AM_SoulSiphon'"));

	if (SevarogSkillAMRef1_2.Object)
	{
		SkillMontage_1.SkillMontages.Add(SevarogSkillAMRef1_2.Object);
	}

	SkillMontage_1.SkillCallbackDelegate.SetNum(2);

	ArrSkillMontage.Add(SkillMontage_1);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> SevarogIntroAMRef(TEXT("/Script/Engine.AnimMontage'/Game/ProectJH/Animation/Enemy/Sevarog/AM_LevelStart.AM_LevelStart'"));

	if (SevarogIntroAMRef.Object)
	{
		LevelStartMontage = (SevarogIntroAMRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> SevarogRageAMRef(TEXT("/Script/Engine.AnimMontage'/Game/ProectJH/Animation/Enemy/Sevarog/AM_RageSkill.AM_RageSkill'"));

	if (SevarogRageAMRef.Object)
	{
		RageSkillMontage = SevarogRageAMRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> SevarogDeadAMRef(TEXT("/Script/Engine.AnimMontage'/Game/ProectJH/Animation/Enemy/Sevarog/AM_Dead.AM_Dead'"));

	if (SevarogDeadAMRef.Object)
	{
		DeadMontage = SevarogDeadAMRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> HitParticleSevRef(TEXT("/Script/Engine.ParticleSystem'/Game/ProectJH/Effect/Sevarog/P_Sevarog_Melee_SucessfulImpact.P_Sevarog_Melee_SucessfulImpact'"));

	if (HitParticleSevRef.Object)
	{
		HitParticleBase = HitParticleSevRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> CastProjParticleRef(TEXT("/Script/Engine.ParticleSystem'/Game/ProectJH/Effect/Sevarog/Proj/P_Fire_Torch_Blue.P_Fire_Torch_Blue'"));

	if (CastProjParticleRef.Object)
	{
		ProjCastParticle = CastProjParticleRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ProjBodyParticleRef(TEXT("/Script/Engine.ParticleSystem'/Game/ProectJH/Effect/Sevarog/P_ky_waterBall.P_ky_waterBall'"));

	if (ProjBodyParticleRef.Object)
	{
		ProjBodyParticle = ProjBodyParticleRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ProjHitParticleRef(TEXT("/Script/Engine.ParticleSystem'/Game/ProectJH/Effect/Sevarog/P_ky_waterBallHit.P_ky_waterBallHit'"));

	if (ProjHitParticleRef.Object)
	{
		ProjHitParticle = ProjHitParticleRef.Object;
	}
	
	AIControllerClass = AJHSevarogAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AJHCharacterSevarog::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AJHCharacterSevarog::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->SetCollisionProfileName(COL_PROFILE_CAPSULE_ENEMY);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -282.0f), FRotator(0.0f, -120.0f, 0.0f));
	GetMesh()->SetWorldScale3D(FVector(1.7f, 1.7f, 1.7f));

	ArrSkillMontage[0].SkillCallbackDelegate[1].BindUObject(this, &AJHCharacterSevarog::TeleportOn);

	PatrolDistance = 500.0f;
	DetectDistance = 1500.0f;
	AttackDistance = 300.0f;
	RageRatio = 0.3f;

	NextComboEnableTime = 1.0f;
	ComboTimeMax = 3.0f;
	GetMesh()->SetVisibility(true);

	ArrProjStartParticle.SetNum(3);

	for (int32 i = 0; i < 3; ++i)
	{
		ArrProjStartParticle[i] = NewObject<UParticleSystemComponent>(this);
		FString SocketName = TEXT("CastProjSocket_0") +  FString::FromInt(i + 1);
		ArrProjStartParticle[i]->SetupAttachment(GetMesh(), FName(SocketName));
		ArrProjStartParticle[i]->SetTemplate(ProjCastParticle);
		ArrProjStartParticle[i]->SetWorldScale3D(FVector(5.0f, 5.0f, 5.0f));
		ArrProjStartParticle[i]->bAutoActivate = false;
		ArrProjStartParticle[i]->RegisterComponent();
	}
}

void AJHCharacterSevarog::SetLevelStart()
{
	UJHAnimInstance* AnimInst = Cast<UJHAnimInstance>(GetMesh()->GetAnimInstance());
	check(AnimInst);
	AnimInst->Montage_Resume(LevelStartMontage);

	GetMesh()->SetVisibility(true);
}

void AJHCharacterSevarog::SetActivateAI()
{
	ActivateAI(true);
}

void AJHCharacterSevarog::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsDead)
	{
		int32 MtrlCnt = GetMesh()->GetMaterials().Num();

		for (int32 i = 0; i < MtrlCnt; ++i)
		{
			UMaterialInstanceDynamic* DynamicMtrl = Cast< UMaterialInstanceDynamic>(GetMesh()->GetMaterial(i));
			FadeOut += DeltaTime * 0.15f;
			DynamicMtrl->SetScalarParameterValue(TEXT("FadeOut"), FadeOut);
		}

		return;
	}

	if (!IsLevelStarted)
	{
		PlayLevelStartMontage();
	}

	if (IsEnableProjSkill)
	{
		SpawnCastProjParticle(DeltaTime);
	}

	if (IsEnableProjFire)
	{
		FireProjectilesTick(DeltaTime);
	}
}

void AJHCharacterSevarog::ProcessComboAttack()
{
	Super::ProcessComboAttack();
}

void AJHCharacterSevarog::AttackFinish()
{
	Super::AttackFinish();
}

void AJHCharacterSevarog::SetDead()
{
	Super::SetDead();

	int32 MtrlCnt = GetMesh()->GetMaterials().Num();

	for (int32 i = 0; i < MtrlCnt; ++i)
	{
		UMaterialInstanceDynamic* DynamicMtrl = UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(i), this);
		GetMesh()->SetMaterial(i, DynamicMtrl);
	}

	
}

float AJHCharacterSevarog::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Damage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	DamageAccumulate += Damage;

	float Ratio = DamageAccumulate / StatComponent->GetMaxHP();

	if (Ratio > RageRatio)
	{
		bIsRage = true;
		DamageAccumulate -= StatComponent->GetMaxHP() * RageRatio;
	}

	return Damage;
}

AJHActorProjectile* AJHCharacterSevarog::SpawnProjectile(const FVector& MoveDir, const FVector& SpawnPos, float MoveSpeed, float MoveTime)
{
	AJHActorProjectile* Projectile = GetWorld()->SpawnActor<AJHActorProjectile>();
	Projectile->SetBodyParticle(ProjBodyParticle);
	Projectile->SetHitParticle(ProjHitParticle);
	Projectile->SetMoveTime(MoveTime);
	Projectile->SetActorLocation(SpawnPos);
	Projectile->SetMoveDir(MoveDir);
	Projectile->SetMoveSpeed(MoveSpeed);
	Projectile->SetCollisionProfile(COL_PROFILE_TRIGGER);

	return Projectile;
}

void AJHCharacterSevarog::StartFireMontage()
{
	if (CastMontage)
	{
		UJHAnimInstance* AnimInst = Cast<UJHAnimInstance>(GetMesh()->GetAnimInstance());

		if (AnimInst)
		{
			AnimInst->Montage_Play(CastMontage);
		}
	}
}

void AJHCharacterSevarog::AdjustFirePos()
{
	IsEnableProjSkill = true;
}

void AJHCharacterSevarog::FireProjectile()
{
	for (int i = 0; i < 3; ++i)
	{
		FString SocketName = TEXT("CastProjSocket_0") + FString::FromInt(i + 1);
		FVector Location = GetWorld()->GetFirstPlayerController()->GetPawn()->GetTransform().GetLocation();
		FVector ParticlePos = GetMesh()->GetSocketLocation(FName(SocketName));
		FVector Dir = Location - ParticlePos;
		Dir.Normalize();

		AJHActorProjectile* Projectile = SpawnProjectile(Dir, ParticlePos, 3000.0f, 5.0f);
		Projectile->SetParticleScale(FVector(3.0f, 3.0f, 3.0f));
		Projectile->SetHitDamage(80.0f);
		Projectile->SetSphereRadius(30.0f);
		Projectile->SetExplodeRadius(100.0f);
		ArrProjStartParticle[i]->Deactivate();
	}
}

AJHStormActor* AJHCharacterSevarog::SpawnStorm(const FVector& SpawnPos, float MoveSpeed, float MoveTime)
{
	AJHStormActor* Storm = GetWorld()->SpawnActor<AJHStormActor>();
	Storm->SetActorLocation(SpawnPos);
	Storm->SetTargetPos(SpawnPos);
	Storm->SetMoveSpeed(MoveSpeed);

	return Storm;
}

void AJHCharacterSevarog::SpawnCastProjParticle(float DeltaTime)
{
	CastTime += DeltaTime;
	
	if (CastTimeMax - CastTime < KINDA_SMALL_NUMBER)
	{
		if (!ArrProjStartParticle.IsValidIndex(CurrentParticleIdx))
		{
			CurrentParticleIdx = 0;
			CastTime = 0.0f;
			IsEnableProjSkill = false;
			IsEnableProjFire = true;
			return;
		}

		ArrProjStartParticle[CurrentParticleIdx]->Activate(false);
		++CurrentParticleIdx;
		CastTime = 0.0f;
	}
}

void AJHCharacterSevarog::FireProjectilesTick(float DeltaTime)
{
	FireTime += DeltaTime;

	if (FireTimeMax - FireTime < KINDA_SMALL_NUMBER)
	{
		FString SocketName = TEXT("CastProjSocket_0") + FString::FromInt(CurrentFireIdx + 1);
		FVector Location = GetWorld()->GetFirstPlayerController()->GetPawn()->GetTransform().GetLocation();
		FVector ParticlePos = GetMesh()->GetSocketLocation(FName(SocketName));
		FVector Dir = Location - ParticlePos;
		Dir.Normalize();

		AJHActorProjectile* Projectile = SpawnProjectile(Dir, ParticlePos, 3000.0f, 2.0f);
		Projectile->SetParticleScale(FVector(2.0f, 2.0f, 2.0f));
		ArrProjStartParticle[CurrentFireIdx]->DeactivateSystem();

		++CurrentFireIdx;
		FireTime = 0.0f;

		if (!ArrProjStartParticle.IsValidIndex(CurrentFireIdx))
		{
			CurrentFireIdx = 0;
			FireTime = 0.0f;
			IsEnableProjFire = false;
			return;
		}

	}
}

void AJHCharacterSevarog::PlayLevelStartMontage()
{
	UJHAnimInstance* AnimInst = Cast<UJHAnimInstance>(GetMesh()->GetAnimInstance());

	if (AnimInst)
	{
		AnimInst->Montage_Play(LevelStartMontage, 1.0f, EMontagePlayReturnType::MontageLength, 0.f, true);
		IsLevelStarted = true;
	}
}

void AJHCharacterSevarog::ExecuteAISkill(const int32 SkillIdx)
{
	CurrentSkillIdx = SkillIdx;
	ProcessSkill();
}

void AJHCharacterSevarog::ProcessSkill()
{
	ProcessNextSkillMontage(ArrSkillMontage[CurrentSkillIdx]);
}

void AJHCharacterSevarog::ProcessRageSkill()
{
	UJHAnimInstance* AnimInst = Cast<UJHAnimInstance>(GetMesh()->GetAnimInstance());
	check(AnimInst);

	AnimInst->StopAllMontages(0.1f);
	AnimInst->Montage_Play(RageSkillMontage);

	SpawnStorm(FVector(-800.000000,2630.000000,-580.000000), 30.0f);
	SpawnStorm(FVector(-2650.000000,780.000000,-580.000000), 30.0f);
	SpawnStorm(FVector(-1670.000000,-1940.000000,-580.000000), 30.0f);
	SpawnStorm(FVector(730.000000,-2500.000000,-580.000000), 30.0f);
	SpawnStorm(FVector(2510.000000,-700.000000,-580.000000), 30.0f);
	SpawnStorm(FVector(1749.354191, 2124.262058, -580.000000), 30.0f);

	bIsRage = false;
}

void AJHCharacterSevarog::SkillFinished()
{
	if (ArrSkillMontage[CurrentSkillIdx].SkillMontages.Num() <= ArrSkillMontage[CurrentSkillIdx].CurrentMontageIdx)
	{
		ArrSkillMontage[CurrentSkillIdx].CurrentMontageIdx = 0;
		CurrentSkillIdx = -1;
		OnSkillFinishedDelegate.ExecuteIfBound();
		return;
	}
}

void AJHCharacterSevarog::SetAISkillFinishedDelegate(const FAISkillFinishedDelegate& Delegate)
{
	OnSkillFinishedDelegate = Delegate;
}

void AJHCharacterSevarog::SetCharacterPause()
{
	UJHAnimInstance* AnimInst = Cast<UJHAnimInstance>(GetMesh()->GetAnimInstance());
	check(AnimInst);

	AnimInst->Montage_Pause(LevelStartMontage);
	
}

void AJHCharacterSevarog::ActivateAI(bool bActive)
{
	Super::ActivateAI(bActive);

	AJHPlayerController* PlayerController = Cast<AJHPlayerController>(GetWorld()->GetFirstPlayerController());
	check(PlayerController);
	PlayerController->SetBossInfo(this);

}

void AJHCharacterSevarog::TeleportOn()
{
	if (CurrentSkillIdx != 0)
	{
		return;
	}

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	FNavLocation TeleportPos;

	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PlayerPawn)
	{
		return;
	}

	FVector PlayerPos = PlayerPawn->GetActorLocation();
	FVector ActorPos = GetActorLocation();

	FVector Dir = PlayerPos - ActorPos;
	Dir.Normalize();
	FVector TargetPos = PlayerPos - Dir * StatComponent->GetAttackRange();

	if (NavSystem->GetRandomPointInNavigableRadius(TargetPos, 30.0f, TeleportPos))
	{
		RootComponent->SetWorldLocation(TeleportPos.Location);
		LookAt(PlayerPos);
		AddActorLocalRotation(FRotator(0.0f, 45.0f, 0.0f));
		FinishTeleport();
	}
	
}

void AJHCharacterSevarog::FinishTeleport()
{
	if (CurrentSkillIdx != 0)
	{
		return;
	}
}

void AJHCharacterSevarog::ProcessNextSkillMontage(FSkillMontages& SkillMontages)
{
	int32 CurrentMontageIdx = SkillMontages.CurrentMontageIdx;

	UAnimMontage* SkillMontage = SkillMontages.SkillMontages[CurrentMontageIdx];

	UJHAnimInstance* AnimInst = Cast<UJHAnimInstance>(GetMesh()->GetAnimInstance());
	check(AnimInst);

	AnimInst->Montage_Play(SkillMontage);
	SkillMontages.SkillCallbackDelegate[CurrentMontageIdx].ExecuteIfBound();

	++SkillMontages.CurrentMontageIdx;
}

void AJHCharacterSevarog::SetupBossWidget(UJHBossWidget* InBossWidget)
{
	Super::SetupBossWidget(InBossWidget);

	InBossWidget->SetBossName(FName(CharacterName));
	InBossWidget->SetMaxHP(StatComponent->GetMaxHP());
	StatComponent->OnHPChanged.AddUObject(InBossWidget, &UJHBossWidget::UpdateHPBar);
	StatComponent->OnHPZero.AddUObject(InBossWidget, &UJHBossWidget::SetBossDead);
}
