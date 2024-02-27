// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_SetAILevelStart.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJH_API UAnimNotify_SetAILevelStart : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UAnimNotify_SetAILevelStart();

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

};
