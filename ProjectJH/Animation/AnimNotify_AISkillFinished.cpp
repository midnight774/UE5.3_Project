// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_AISkillFinished.h"
#include "Interface/JHAISkillInterface.h"

UAnimNotify_AISkillFinished::UAnimNotify_AISkillFinished()
{
}

void UAnimNotify_AISkillFinished::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		IJHAISkillInterface* AISkillInterface = Cast<IJHAISkillInterface>(MeshComp->GetOwner());

		if (AISkillInterface)
		{
			AISkillInterface->SkillFinished();
		}
	}
}
