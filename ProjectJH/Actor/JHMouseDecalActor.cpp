// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/JHMouseDecalActor.h"
#include "Components/DecalComponent.h"
#include "Player/JHPlayerController.h"

// Sets default values
AJHMouseDecalActor::AJHMouseDecalActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMtrlRef(TEXT("/Script/Engine.Material'/Game/ProectJH/Material/TestDecalMaterial.TestDecalMaterial'"));
	if (DecalMtrlRef.Object)
	{
		SetDecalMaterial(DecalMtrlRef.Object);
	}
}

// Called when the game starts or when spawned
void AJHMouseDecalActor::BeginPlay()
{
	Super::BeginPlay();
	
	GetDecal()->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	GetDecal()->bDestroyOwnerAfterFade = true;

}

// Called every frame
void AJHMouseDecalActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetDecal()->AddRelativeRotation(FRotator(0.0f, 0.0f, 30.0f * DeltaTime));
}

