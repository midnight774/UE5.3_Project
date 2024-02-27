// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_Defence_End.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJH_API UAnimNotify_Defence_End : public UAnimNotify
{
	GENERATED_BODY()

public:
	UAnimNotify_Defence_End();

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
};
