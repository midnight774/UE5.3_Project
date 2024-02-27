// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_GetRandomSkillKey.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJH_API UBTService_GetRandomSkillKey : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_GetRandomSkillKey();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
