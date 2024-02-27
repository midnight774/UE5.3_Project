// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_DecidePatrolPos.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJH_API UBTTask_DecidePatrolPos : public UBTTaskNode
{
	GENERATED_BODY()
	

public:
	UBTTask_DecidePatrolPos();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
