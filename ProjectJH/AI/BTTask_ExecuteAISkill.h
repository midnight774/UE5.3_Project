// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ExecuteAISkill.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJH_API UBTTask_ExecuteAISkill : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_ExecuteAISkill();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
