// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_SetRandSkillNum.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJH_API UBTDecorator_SetRandSkillNum : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_SetRandSkillNum();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
