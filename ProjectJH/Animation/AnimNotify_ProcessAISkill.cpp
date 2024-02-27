// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_ProcessAISkill.h"
#include "Interface/JHAISkillInterface.h"

UAnimNotify_ProcessAISkill::UAnimNotify_ProcessAISkill()
{
}

void UAnimNotify_ProcessAISkill::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		IJHAISkillInterface* AISkillInterface = Cast<IJHAISkillInterface>(MeshComp->GetOwner());

		if (AISkillInterface)
		{
			AISkillInterface->ProcessSkill();
		}
	}
}
