// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsProcessingCombo.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJH_API UBTDecorator_IsProcessingCombo : public UBTDecorator
{
	GENERATED_BODY()
	

public:
	UBTDecorator_IsProcessingCombo();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
