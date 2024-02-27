// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "JHEnemyAIInterface.generated.h"


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UJHEnemyAIInterface : public UInterface
{
	GENERATED_BODY()
};

DECLARE_DELEGATE(FAIAttackFinishedDelegate)

/**
 * 
 */
class PROJECTJH_API IJHEnemyAIInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual float GetPatrolDistance() = 0;
	virtual float GetDetectDistance() = 0;
	virtual float GetAttackDistance() = 0;
	virtual float GetTaskChangeTime() = 0;

	virtual void AIAttack() = 0;
	virtual void AILookAtTarget(const FVector& TargetPos) = 0;
	virtual void AIMoveToTarget() = 0;

	virtual bool IsAIAttackEnded() = 0;
	virtual void SetAttackFinishedDelegate(const FAIAttackFinishedDelegate& Delegate) = 0;
	virtual void ActivateAI(bool bActive) = 0;
	virtual void SetAILevelStart() = 0;

	virtual bool IsRageOn() = 0;

};
