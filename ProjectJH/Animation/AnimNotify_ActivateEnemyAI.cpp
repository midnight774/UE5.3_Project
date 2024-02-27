// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_ActivateEnemyAI.h"
#include "Interface/JHEnemyAIInterface.h"

UAnimNotify_ActivateEnemyAI::UAnimNotify_ActivateEnemyAI()
{
}

void UAnimNotify_ActivateEnemyAI::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	IJHEnemyAIInterface* AIInterface = Cast<IJHEnemyAIInterface>(MeshComp->GetOwner());
	
	if (AIInterface)
	{
		AIInterface->ActivateAI(true);
	}
}
