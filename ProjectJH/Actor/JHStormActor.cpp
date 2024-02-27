// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/JHStormActor.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Collision/JHCollision.h"
#include "Engine/DamageEvents.h"
#include "NavigationSystem.h"

// Sets default values
AJHStormActor::AJHStormActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BodyBox= CreateDefaultSubobject<UBoxComponent>(TEXT("BodyBox"));
	SetRootComponent(BodyBox);

	BodyParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("StormBodyParticle"));
	BodyParticle->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> BodyParticleRef(TEXT("/Script/Engine.ParticleSystem'/Game/ProectJH/Effect/Sevarog/P_ky_storm.P_ky_storm'"));

	if (BodyParticleRef.Object)
	{
		BodyParticle->SetTemplate(BodyParticleRef.Object);
		BodyParticle->bAutoActivate = true;
	}

	HitParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("StormHitParticle"));
	HitParticle->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> HitParticleRef(TEXT("/Script/Engine.ParticleSystem'/Game/ProectJH/Effect/Sevarog/P_Sevarog_Melee_SucessfulImpact.P_Sevarog_Melee_SucessfulImpact'"));

	if (HitParticleRef.Object)
	{
		HitParticle->SetTemplate(HitParticleRef.Object);
		HitParticle->bAutoActivate = false;
	}

	MoveTimeMax = 10.0f;
	MoveTime = 0.0f;

	ChangeDirTimeMax = 3.0f;
	ChangeDirTime = 0.0f;
}

void AJHStormActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

// Called when the game starts or when spawned
void AJHStormActor::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(FVector(0.0f, 0.0f, 0.0f));
	BodyBox->SetBoxExtent(FVector(70.0f, 70.0f, 500.0f));
	
	BodyBox->SetCollisionProfileName(COL_PROFILE_TRIGGER);
	BodyBox->OnComponentBeginOverlap.AddDynamic(this, &AJHStormActor::HitEvent);

	MoveTimeMax = 10.0f;
	TargetScale = FVector(2.0f, 2.0f, 2.0f);
}

// Called every frame
void AJHStormActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ScaleTick(DeltaTime);
}

void AJHStormActor::ScaleTick(float DeltaTime)
{
	FVector CurrentScale = GetActorScale3D();
	if (!IsMoving)
	{
		if (TargetScale.X - CurrentScale.X > KINDA_SMALL_NUMBER)
		{
			CurrentScale.X += DeltaTime * 0.5f;
			CurrentScale.Y = CurrentScale.X;
			CurrentScale.Z = CurrentScale.X;

			SetActorScale3D(CurrentScale);
		}

		else
		{
			SetActorScale3D(TargetScale);
			IsMoving = true;
		}
	}

	else
	{
		FVector CurrentPos = GetActorLocation();
		float TargetDist = FVector::Dist(CurrentPos, TargetPos);
		ChangeDirTime += DeltaTime;

		if (TargetDist < KINDA_SMALL_NUMBER || ChangeDirTimeMax - ChangeDirTime < KINDA_SMALL_NUMBER)
		{
			DecideRandTargetPos();
			ChangeDirTime = 0.0f;
		}

		FVector NewMoveDir = TargetPos - CurrentPos;
		NewMoveDir.Normalize();
		NewMoveDir.Z = 0.0f;

		FVector NewPos = GetActorLocation() + NewMoveDir * MoveSpeed;;
		SetActorLocation(NewPos);

		if (MoveTimeMax - MoveTime > KINDA_SMALL_NUMBER)
		{
			MoveTime += DeltaTime;
		}

		else
		{
			if (CurrentScale.X > KINDA_SMALL_NUMBER)
			{
				CurrentScale.X -= DeltaTime * 0.5f;
				CurrentScale.Y -= DeltaTime * 0.5f;
				CurrentScale.Z -= DeltaTime * 0.5f;

				SetActorScale3D(CurrentScale);
			}

			else
			{
				Destroy();
			}
		}

		
	}
}

void AJHStormActor::SetBodyParticle(UParticleSystem* ParticleSystem, bool bActivate)
{
}

void AJHStormActor::SetHitParticle(UParticleSystem* ParticleSystem)
{
}

void AJHStormActor::LookDir()
{
}

void AJHStormActor::DecideRandTargetPos()
{
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	FNavLocation NewTargetLocation;

	if (NavSystem->GetRandomPoint(NewTargetLocation))
	{
		TargetPos = NewTargetLocation.Location;
	}
}

void AJHStormActor::SetParticleScale(const FVector& InScale)
{
}

void AJHStormActor::SetSphereRadius(float InRadius)
{
}

void AJHStormActor::SetCollisionProfile(const FString& ProfileName)
{
}

void AJHStormActor::HitEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FDamageEvent DamageEvent;

	//SweepResult.ImpactPoint
	OtherActor->TakeDamage(80.0f, DamageEvent,nullptr, this);
}

