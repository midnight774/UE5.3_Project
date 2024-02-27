// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_RSkillAttackCheck.h"
#include "Interface/JHPlayerSkillInterface.h"

UAnimNotify_RSkillAttackCheck::UAnimNotify_RSkillAttackCheck()
{
}

void UAnimNotify_RSkillAttackCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		IJHPlayerSkillInterface* SkillInterface = Cast<IJHPlayerSkillInterface>(MeshComp->GetOwner());

		if (SkillInterface)
		{
			SkillInterface->RSkillAttackCheck();
		}
	}
}
