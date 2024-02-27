// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_PauseCharacter.h"
#include "Interface/JHAISkillInterface.h"

void UAnimNotify_PauseCharacter::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		IJHAISkillInterface* SkillInterface = Cast<IJHAISkillInterface>(MeshComp->GetOwner());

		if (SkillInterface)
		{
			SkillInterface->SetCharacterPause();
		}
	}
}
