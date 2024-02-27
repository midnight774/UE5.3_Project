// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/JHDissolveComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values for this component's properties
UJHDissolveComponent::UJHDissolveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bDissolveEnded = false;

	Dissolve = 0.0f;
	DissolveMax = 1.0f;
	DissolveSpeed = 0.5f;

	// ...
}


// Called when the game starts
void UJHDissolveComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	DissolveMaterialInst = UMaterialInstanceDynamic::Create(TargetSkeletal->GetMaterial(0), this);
	TargetSkeletal->SetMaterial(0, DissolveMaterialInst);
}


// Called every frame
void UJHDissolveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bDissolveEnable)
	{
		if (bDissolveRev)
		{
			Dissolve -= DeltaTime * DissolveSpeed;

			if (Dissolve < KINDA_SMALL_NUMBER)
			{
				bDissolveEnable = false;
				bDissolveEnded = true;
			}
		}

		else
		{
			Dissolve += DeltaTime * DissolveSpeed;
			
			if (DissolveMax - Dissolve  < KINDA_SMALL_NUMBER)
			{
				bDissolveEnable = false;
				bDissolveEnded = true;
			}
		}
		
		if (DissolveMaterialInst)
		{
			DissolveMaterialInst->SetScalarParameterValue(TEXT("Dissolve"), Dissolve);
		}
	}

	// ...
}

void UJHDissolveComponent::SetDissolveReverse(bool IsRev)
{
	bDissolveRev = IsRev;
	Dissolve = IsRev ? 1.0f : 0.0f;
}

