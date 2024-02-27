// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_Defence_Start.h"
#include "Interface/JHAnimationDefenceInterface.h"

UAnimNotify_Defence_Start::UAnimNotify_Defence_Start()
{
}

void UAnimNotify_Defence_Start::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		IJHAnimationDefenceInterface* DefenceInterface = Cast<IJHAnimationDefenceInterface>(MeshComp->GetOwner());

		if (DefenceInterface)
		{
			DefenceInterface->SetDefenceEnable(true);
		}
	}
}
