// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_PauseMontage.h"
#include "Interface/JHPlayerSkillInterface.h"

UAnimNotify_PauseMontage::UAnimNotify_PauseMontage()
{
}

void UAnimNotify_PauseMontage::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		IJHPlayerSkillInterface* SkillInterface = Cast<IJHPlayerSkillInterface>(MeshComp->GetOwner());

		if (SkillInterface)
		{
			SkillInterface->PauseMontage();
		}
	}
}
