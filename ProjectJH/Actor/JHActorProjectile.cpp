// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/JHActorProjectile.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/DamageEvents.h"
#include "Sound/SoundWave.h"
#include "Collision/JHCollision.h"
#include "Components/AudioComponent.h"

// Sets default values
AJHActorProjectile::AJHActorProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BodySphere = CreateDefaultSubobject<USphereComponent>(TEXT("BodySphere"));
	SetRootComponent(BodySphere);

	BodyParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BodyParticle"));
	BodyParticle->SetupAttachment(RootComponent);


	HitParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("HitParticle"));
	HitParticle->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<USoundWave> DefaultHitSoundRef(TEXT("/Script/Engine.SoundWave'/Game/ProectJH/Audio/WavFile/Fire_Explosion.Fire_Explosion'"));

	if (DefaultHitSoundRef.Object)
	{
		HitSound = DefaultHitSoundRef.Object;
	}
}

void AJHActorProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttackDamage = 150.0f;
	AttackRadius = 300.0f;
}

// Called when the game starts or when spawned
void AJHActorProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	MoveTime = 0.0f;
	bIsMoving = true;
	IsExploded = false;

	BodyParticle->SetWorldScale3D(FVector(2.0f, 2.0f, 2.0f));
	BodyParticle->bAutoActivate = true;
	BodyParticle->Activate(true);
	HitParticle->SetWorldScale3D(FVector(5.0f, 5.0f, 5.0f));
	HitParticle->bAutoActivate = false;

	BodySphere->InitSphereRadius(30.0f);
	BodySphere->OnComponentBeginOverlap.AddDynamic(this, &AJHActorProjectile::HitEvent);
	HitParticle->OnSystemFinished.AddDynamic(this, &AJHActorProjectile::SystemFinished);
}

// Called every frame
void AJHActorProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LookDir();

	if (bIsMoving)
	{
		MoveTime += DeltaTime;

		if (MoveTimeMax - MoveTime < KINDA_SMALL_NUMBER)
		{
			ExplosionHitCheck();
			BodyParticle->Deactivate();
			HitParticle->Activate(true);
			bIsMoving = false;
		}

		FTransform Transform;
		Transform.AddToTranslation(DeltaTime * MoveDir * MoveSpeed);
		AddActorWorldTransform(Transform);
	}
}

void AJHActorProjectile::SetBodyParticle(UParticleSystem* ParticleSystem, bool bActivate)
{
	if (ParticleSystem && BodyParticle)
	{
		BodyParticle->SetTemplate(ParticleSystem);
	}
}

void AJHActorProjectile::SetHitParticle(UParticleSystem* ParticleSystem)
{
	if (ParticleSystem && HitParticle)
	{
		HitParticle->SetTemplate(ParticleSystem);
	}
}

void AJHActorProjectile::LookDir()
{
	FVector LookDir = MoveDir;

	LookDir.Normalize();

	FRotator TargetRot = FRotationMatrix::MakeFromX(LookDir).Rotator();
	SetActorRotation(FMath::RInterpTo(GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 90.0f));
}

void AJHActorProjectile::SetParticleScale(const FVector& InScale)
{
	HitParticle->SetWorldScale3D(InScale);
	BodyParticle->SetWorldScale3D(InScale);
}

void AJHActorProjectile::SetSphereRadius(float InRadius)
{
	BodySphere->SetSphereRadius(InRadius);
}

void AJHActorProjectile::SetCollisionProfile(const FString& ProfileName)
{
	BodySphere->SetCollisionProfileName(FName(ProfileName));
}

void AJHActorProjectile::HitEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsExploded)
	{
		return;
	}

	IsExploded = true;

	ExplosionHitCheck();
	BodyParticle->Deactivate();
	HitParticle->Activate(true);
	bIsMoving = false;
}

void AJHActorProjectile::ExplosionHitCheck()
{
	UAudioComponent* AudioComp = NewObject<UAudioComponent>(this);
	AudioComp->SetSound(HitSound);
	AudioComp->Activate(false);
	AudioComp->RegisterComponent();
	AudioComp->SetVolumeMultiplier(4.0f);

	TArray<FOverlapResult> OutHitResults;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);
	Params.AddIgnoredActor(this);

	bool HitDetected = GetWorld()->OverlapMultiByChannel(OutHitResults, GetActorLocation(), FQuat::Identity, COL_CHANNEL_ACTION_ENEMY, FCollisionShape::MakeSphere(AttackRadius), Params);

	if (HitDetected)
	{
		FDamageEvent DamageEvent;

		for (FOverlapResult Result : OutHitResults)
		{
			Result.GetActor()->TakeDamage(AttackDamage, DamageEvent, nullptr, this);

			TObjectPtr<UParticleSystemComponent> ParticleComp = NewObject<UParticleSystemComponent>(this);
		}
	}

#if ENABLE_DRAW_DEBUG

	FColor DrawColor = HitDetected ? FColor::Red : FColor::Green;

	DrawDebugSphere(GetWorld(), GetActorLocation(), AttackRadius,16, DrawColor, false, 0.5f);

#endif
}

void AJHActorProjectile::SystemFinished(UParticleSystemComponent* PSystem)
{
	Destroy();
}

