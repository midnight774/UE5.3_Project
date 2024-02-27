// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_BossDetectPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJH_API UBTService_BossDetectPlayer : public UBTService
{
	GENERATED_BODY()


protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
