// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_AttackCollisionCheck.h"
#include "Interface/JHAnimationAttackInterface.h"

UAnimNotify_AttackCollisionCheck::UAnimNotify_AttackCollisionCheck()
{
}

void UAnimNotify_AttackCollisionCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		IJHAnimationAttackInterface* AttackInterface = Cast<IJHAnimationAttackInterface>(MeshComp->GetOwner());

		if (AttackInterface)
		{
			AttackInterface->AttackHitCheck();
		}
	}
}
