// Fill out your copyright notice in the Description page of Project Settings.

#include "Actor/JHGhostTrailActor.h"
#include "GameFramework/Character.h"
#include "Components/PoseableMeshComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
AJHGhostTrailActor::AJHGhostTrailActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	SceneRootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(SceneRootComp);

	PoseableMeshComp = CreateDefaultSubobject<UPoseableMeshComponent>(TEXT("PoseableMeshComp"));
	PoseableMeshComp->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> GhostMtrlRef(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/ProectJH/Material/MI_GhostTrail.MI_GhostTrail'"));

	if (GhostMtrlRef.Object)
	{
		GhostTrailMaterial = GhostMtrlRef.Object;
	}
	
	GhostColor = FColor::White;
}

// Called when the game starts or when spawned
void AJHGhostTrailActor::BeginPlay()
{
	Super::BeginPlay();
}

void AJHGhostTrailActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsActive)
	{
		UpdateEffectOpacity(DeltaTime);
	}

}

void AJHGhostTrailActor::SetActiveGhost()
{
	IsActive = true;
	SetupPoseableMeshInfo();
}

void AJHGhostTrailActor::SetMeshRelativeLocation(const FVector& InLocation)
{
	PoseableMeshComp->SetRelativeLocation(InLocation);
}

void AJHGhostTrailActor::SetMeshRelativeRotation(const FRotator& InRotation)
{
	PoseableMeshComp->SetRelativeRotation(InRotation);
}

void AJHGhostTrailActor::SetMeshRelativeScale(const FVector& InScale)
{
	PoseableMeshComp->SetRelativeScale3D(InScale);
}

void AJHGhostTrailActor::SetupPoseableMeshInfo()
{
	DynamicMtrlInstance = UMaterialInstanceDynamic::Create(GhostTrailMaterial, this);
	DynamicMtrlInstance->SetVectorParameterValue(TEXT("Color"), GhostColor);

	check(CharacterRef);

	PoseableMeshComp->SetSkeletalMesh(CharacterRef->GetMesh()->GetSkeletalMeshAsset());
	PoseableMeshComp->CopyPoseFromSkeletalComponent(CharacterRef->GetMesh());

	int32 MtrlCnt = CharacterRef->GetMesh()->GetMaterials().Num();

	for (int32 i = 0; i < MtrlCnt; ++i)
	{
		PoseableMeshComp->SetMaterial(i, DynamicMtrlInstance);
	}

	Opacity = 1.0f;
}

void AJHGhostTrailActor::UpdateEffectOpacity(float DeltaTime)
{
	Opacity -= DeltaTime * 2.0f;

	DynamicMtrlInstance->SetScalarParameterValue(TEXT("Opacity"), Opacity);

	if (Opacity < KINDA_SMALL_NUMBER)
	{
		Destroy();
	}
}

