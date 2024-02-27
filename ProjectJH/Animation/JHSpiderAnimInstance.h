// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/JHAnimInstance.h"
#include "JHSpiderAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJH_API UJHSpiderAnimInstance : public UJHAnimInstance
{
	GENERATED_BODY()

public:
	UJHSpiderAnimInstance();

protected:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;	
};
