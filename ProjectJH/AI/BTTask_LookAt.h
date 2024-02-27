// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_LookAt.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJH_API UBTTask_LookAt : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_LookAt();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
