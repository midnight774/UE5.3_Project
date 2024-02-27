// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/JHChangeLevelActor.h"
#include "Components/BoxComponent.h"
#include "Collision/JHCollision.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AJHChangeLevelActor::AJHChangeLevelActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("LevelChangeVolume"));
}

// Called when the game starts or when spawned
void AJHChangeLevelActor::BeginPlay()
{
	Super::BeginPlay();

	TriggerVolume->SetCollisionProfileName(COL_PROFILE_TRIGGER);
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AJHChangeLevelActor::OnBeginOverlapLevelTrigger);
	
}

// Called every frame
void AJHChangeLevelActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJHChangeLevelActor::OnBeginOverlapLevelTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		UGameplayStatics::OpenLevel(this, FName(NextLevelName));
	}
}

