// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_Defence_End.h"
#include "Interface/JHAnimationDefenceInterface.h"

UAnimNotify_Defence_End::UAnimNotify_Defence_End()
{
}

void UAnimNotify_Defence_End::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		IJHAnimationDefenceInterface* DefenceInterface = Cast<IJHAnimationDefenceInterface>(MeshComp->GetOwner());

		if (DefenceInterface)
		{
			DefenceInterface->SetDefenceEnable(false);
		}
	}
}
