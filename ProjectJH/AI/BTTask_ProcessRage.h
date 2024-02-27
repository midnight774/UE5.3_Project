// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ProcessRage.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJH_API UBTTask_ProcessRage : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_ProcessRage();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
