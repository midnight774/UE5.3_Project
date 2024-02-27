// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_QSkill.h"
#include "Interface/JHPlayerSkillInterface.h"

UAnimNotify_QSkill::UAnimNotify_QSkill()
{
}

void UAnimNotify_QSkill::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		IJHPlayerSkillInterface* SkillInterface = Cast<IJHPlayerSkillInterface>(MeshComp->GetOwner());

		if (SkillInterface)
		{
			SkillInterface->QSkillNotifyAction();
		}
	}
}
