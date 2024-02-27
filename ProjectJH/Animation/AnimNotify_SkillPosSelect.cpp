// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_SkillPosSelect.h"
#include "AnimNotify_SkillPosSelect.h"

UAnimNotify_SkillPosSelect::UAnimNotify_SkillPosSelect()
{
}

void UAnimNotify_SkillPosSelect::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
}
