// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_AttackEnd.h"
#include "Interface/JHAnimationAttackInterface.h"

UAnimNotify_AttackEnd::UAnimNotify_AttackEnd()
{
}

void UAnimNotify_AttackEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		IJHAnimationAttackInterface* AttackInterface = Cast<IJHAnimationAttackInterface>(MeshComp->GetOwner());

		if (AttackInterface)
		{
			AttackInterface->AttackFinish();
		}
	}
}
