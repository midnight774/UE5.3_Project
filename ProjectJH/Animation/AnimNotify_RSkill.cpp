// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_RSkill.h"
#include "Interface/JHPlayerSkillInterface.h"

UAnimNotify_RSkill::UAnimNotify_RSkill()
{
}

void UAnimNotify_RSkill::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		IJHPlayerSkillInterface* SkillInterface = Cast<IJHPlayerSkillInterface>(MeshComp->GetOwner());

		if (SkillInterface)
		{
			SkillInterface->RSkillNotifyAction();
		}
	}
}
