// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_SetAILevelStart.h"
#include "Interface/JHEnemyAIInterface.h"

UAnimNotify_SetAILevelStart::UAnimNotify_SetAILevelStart()
{
}

void UAnimNotify_SetAILevelStart::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	IJHEnemyAIInterface* AIInterface = Cast<IJHEnemyAIInterface>(MeshComp->GetOwner());

	if (AIInterface)
	{
		AIInterface->SetAILevelStart();
	}
}
