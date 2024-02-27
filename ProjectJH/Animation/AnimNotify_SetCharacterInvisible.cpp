// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_SetCharacterInvisible.h"

void UAnimNotify_SetCharacterInvisible::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	MeshComp->SetVisibility(false);
}
