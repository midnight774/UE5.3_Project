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

	int32 MtrlCount = TargetSkeletal->GetNumMaterials();
	ArrDissolveMaterialInst.SetNum(MtrlCount);

	for (int32 i = 0; i < MtrlCount; ++i)
	{
		ArrDissolveMaterialInst[i] = UMaterialInstanceDynamic::Create(TargetSkeletal->GetMaterial(i), this);
		TargetSkeletal->SetMaterial(i, ArrDissolveMaterialInst[i]);
	}
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
		
		int32 MtrlCount = ArrDissolveMaterialInst.Num();

		for (int32 i = 0; i < MtrlCount; ++i)
		{
			ArrDissolveMaterialInst[i]->SetScalarParameterValue(TEXT("Dissolve"), Dissolve);
		}
	}
}

void UJHDissolveComponent::SetDissolveReverse(bool IsRev)
{
	bDissolveRev = IsRev;
	Dissolve = IsRev ? 1.0f : 0.0f;
}

