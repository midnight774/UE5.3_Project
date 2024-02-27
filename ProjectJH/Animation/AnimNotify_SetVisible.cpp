// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_SetVisible.h"

void UAnimNotify_SetVisible::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp)
	{
		MeshComp->SetVisibility(true, true);
	}
}
