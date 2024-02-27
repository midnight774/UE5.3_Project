// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/JHCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Collision/JHCollision.h"
#include "Engine/DamageEvents.h"
#include "Animation/JHAnimInstance.h"
#include "CharacterStat/JHCharacterStatComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "NavigationSystem.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "JHCharacterEnemy.h"
#include "Actor/JHActorProjectile.h"

// Sets default values
AJHCharacterBase::AJHCharacterBase() :	DeadDelayTime(0.0f), 
										DeadDelayTimeMax(3.0f),
										HitTime(0.0f),
										HitTimeMax(0.3f),
										IsTargetLooking(false)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Pawn
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll	= false;
	bUseControllerRotationYaw	= true;


	//Capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 84.0f);
	GetCapsuleComponent()->SetCollisionProfileName(COL_PROFILE_CAPSULE);
	 
	//Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	//Mesh Defulat Collision Setting
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	IsDead = false;

	//Stat Setting
	StatComponent = CreateDefaultSubobject<UJHCharacterStatComponent>(TEXT("StatComponent"));

	static ConstructorHelpers::FObjectFinder<UParticleSystem> HitParticleRef(TEXT("/Script/Engine.ParticleSystem'/Game/ProectJH/Effect/P_ImpactSpark.P_ImpactSpark'"));

	if (HitParticleRef.Object)
	{
		HitParticleBase = HitParticleRef.Object;
	}
}

void AJHCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	StatComponent->SetCharacterStatByName(CharacterName);
}

// Called when the game starts or when spawned
void AJHCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	ComboCountMax = ArrAttackMontage.Num();
	ComboTime = 0.0f;
	NextComboEnableTime = 0.5f;
	ComboTimeMax = 1.5f;

	StatComponent->GetMaxHP();
	StatComponent->GetMaxMP();

	StatComponent->OnHPZero.AddUObject(this, &AJHCharacterBase::SetDead);
	GetCharacterMovement()->MaxWalkSpeed = StatComponent->GetMoveSpeed();
}

// Called every frame
void AJHCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DefaultAttackTick(DeltaTime);

	if (IsHitted)
	{
		HitTime += DeltaTime;

		if (HitTimeMax - HitTime < KINDA_SMALL_NUMBER)
		{
			IsHitted = false;
			HitTime = 0.0f;
			UJHAnimInstance* AnimInst = Cast<UJHAnimInstance>(GetMesh()->GetAnimInstance());
			AnimInst->SetHitted(false);
			IsAutoMoving = false;
		}
	}

	if (IsAutoMoving)
	{
		AutoMove(DeltaTime);
	}

	if (IsTargetLooking)
	{
		LookAt(LookTargetPos);
	}
}

void AJHCharacterBase::DefaultAttackTick(float DeltaTime)
{
	if (IsPrecessCombo)
	{
		ComboTime += DeltaTime;

		if (ComboTimeMax - ComboTime < KINDA_SMALL_NUMBER)
		{
			ComboTime = 0.0f;
			IsPrecessCombo = false;
			CurrentComboCount = 0;

			AttackFinish();
		}
	}
	
	if (IsDead)
	{
		DeadDelayTime += DeltaTime;

		if (DeadDelayTimeMax - DeadDelayTime < KINDA_SMALL_NUMBER)
		{
			DestroyCallback();
			Destroy();
		}
	}
}

// Called to bind functionality to input
void AJHCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AJHCharacterBase::ProcessComboAttack()
{
	UAnimInstance* AnimInst = GetMesh()->GetAnimInstance();

	if (AnimInst)
	{
		if (!IsPrecessCombo)
		{
			AnimInst->Montage_Play(ArrAttackMontage[0], StatComponent->GetAttackSpeed());
			++CurrentComboCount;
			IsPrecessCombo = true;
		}

		else
		{
			if (CurrentComboCount >= ComboCountMax)
			{
				return;
			}
			
			if (ComboTimeMax - ComboTime > KINDA_SMALL_NUMBER)
			{
				if (ComboTime - NextComboEnableTime > KINDA_SMALL_NUMBER)
				{
					AnimInst->Montage_Play(ArrAttackMontage[CurrentComboCount], StatComponent->GetAttackSpeed());
					++CurrentComboCount;
					ComboTime = 0.0f;
				}
			}
		}
	}
}

void AJHCharacterBase::AttackFinish()
{
	CurrentComboCount = 0;
	ComboTime = 0.0f;

	if (AttackEndMontage)
	{
		UAnimInstance* AnimInst = GetMesh()->GetAnimInstance();

		AnimInst->Montage_Play(AttackEndMontage, 0.5f);
	}
}

void AJHCharacterBase::SetDead()
{
	if (IsDead)
	{
		return;
	}

	PlayDeadAnimation();
	IsDead = true;
	SetActorEnableCollision(false);
}

void AJHCharacterBase::DestroyCallback()
{
}

void AJHCharacterBase::LookAt(const FVector& TargetPos)
{
	FVector CharacterPos = GetActorLocation();
	FVector LookDir = TargetPos - CharacterPos;

	LookDir.Normalize();
	LookDir.Z = 0.0f;

	FRotator TargetRot = FRotationMatrix::MakeFromX(LookDir).Rotator();
	SetActorRotation(FMath::RInterpTo(GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 30.0f));
}

void AJHCharacterBase::MoveTo(const FVector& TargetPos)
{
	IsAutoMoving = true;
	AutoMoveTargetPos = TargetPos;
}

void AJHCharacterBase::AutoMove(float DeltaTime)
{
	FVector CurrentPos = GetActorLocation();
	FVector Dir = AutoMoveTargetPos - CurrentPos;
	Dir.Normalize(); 
	
	if (FMath::Abs(FVector::Distance(CurrentPos, AutoMoveTargetPos)) < 10.0f)
	{
		IsAutoMoving = false;
	}

	RootComponent->AddRelativeLocation(Dir * StatComponent->GetMoveSpeed() * DeltaTime);

	
}

void AJHCharacterBase::PlayDeadAnimation()
{
	UAnimInstance* AnimInst = GetMesh()->GetAnimInstance();

	if (nullptr == AnimInst)
	{
		return;
	}

	if (DeadMontage)
	{
		AnimInst->StopAllMontages(0.0f);
		AnimInst->Montage_Play(DeadMontage);
	}
}

float AJHCharacterBase::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Damage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (IsDefenceSucceeded())
	{
		return 0.0f;
	}

	Damage = StatComponent->ApplyDamage(Damage);

	IsHitted = true;
	HitTime = 0.0f;

	FVector CauserPos = DamageCauser->GetActorLocation();
	FVector CharacterPos = GetActorLocation();
	FVector CharacterUpDir = GetActorUpVector();
	
	FVector CauserDir = CauserPos - CharacterPos;
	CauserDir.Normalize();

	FVector CharacterForwardDir = GetActorForwardVector();

	//앞뒤 판별
	float FrontHitDirRadian = FVector::DotProduct(CharacterForwardDir, CauserDir);

	//양 옆 판별
	FVector CrossDir = FVector::CrossProduct(CharacterForwardDir, CauserDir);
	float SideHitDirRadian = FVector::DotProduct(CharacterUpDir, CrossDir);

	UJHAnimInstance* AnimInst = Cast<UJHAnimInstance>(GetMesh()->GetAnimInstance());

	if (AnimInst)
	{
		AnimInst->SetHitted(IsHitted);
		AnimInst->SetHitFrontDir(FrontHitDirRadian);
		AnimInst->SetHitSideDir(SideHitDirRadian);
	}

	return Damage;
}

void AJHCharacterBase::AttackHitCheck()
{
	TArray<FHitResult> OutHitResults;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);
	Params.AddIgnoredActor(this);

	const float AttackRange =  StatComponent->GetAttackRange();
	const float AttackRadius = StatComponent->GetAttackRange();
	const float AttackDamage = StatComponent->GetAttack();
	const FVector Start = GetActorLocation() + GetActorForwardVector() * GetCapsuleComponent()->GetScaledCapsuleRadius();
	const FVector End = Start + GetActorForwardVector() * AttackRange;

	ECollisionChannel ColChannel = COL_CHANNEL_ACTION;

	if (Cast<AJHCharacterEnemy>(this))
	{
		ColChannel = COL_CHANNEL_ACTION_ENEMY;
	}

	bool HitDetected = GetWorld()->SweepMultiByChannel(OutHitResults, Start, End, FQuat::Identity, ColChannel, FCollisionShape::MakeSphere(AttackRadius), Params);

	if (HitDetected)
	{
		FDamageEvent DamageEvent;

		HitSucceededCallback();

		for (FHitResult Result : OutHitResults)
		{
			Result.GetActor()->TakeDamage(AttackDamage, DamageEvent, GetController(), this);
			
			TObjectPtr<UParticleSystemComponent> ParticleComp = NewObject<UParticleSystemComponent>(this);

			HitParticleBase->bAutoDeactivate = true;
			ParticleComp->SetupAttachment(RootComponent);
			ParticleComp->SetTemplate(HitParticleBase);
			ParticleComp->Activate(true);
			ParticleComp->SetWorldLocation(Result.ImpactPoint);
			ParticleComp->RegisterComponent();
		}
	}

#if ENABLE_DRAW_DEBUG

	FVector CapsuleOrigin = Start + (End - Start) * 0.5f;
	float CapsuleHalfHeight = AttackRange * 0.5f;
	FColor DrawColor = HitDetected ? FColor::Red : FColor::Green;

	DrawDebugCapsule(GetWorld(), CapsuleOrigin, CapsuleHalfHeight, AttackRadius, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), DrawColor, false, 1.0f);

#endif
}

void AJHCharacterBase::HitSucceededCallback()
{
}

void AJHCharacterBase::SetDefenceEnable(bool Enable)
{
	bIsDefending = Enable;

	if (Enable)
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	}

	else
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	}
}

bool AJHCharacterBase::IsDefenceSucceeded()
{
	if (bIsDefending)
	{
		if (DefenceEffect)
		{
			DefenceEffect->Activate(true);
		}

		bIsDefending = false;
		GetWorldSettings()->SetTimeDilation(0.3f);

		FTimerDelegate TimerDelegate;

		TimerDelegate.BindLambda(
			[&]()
			{
				GetWorldSettings()->SetTimeDilation(1.0f);
				GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
			}
		);

		GetWorld()->GetTimerManager().SetTimer(SlowTimeHandle, TimerDelegate, 1.0f, false, 0.5f);

		return true;
	}

	return false;
}

