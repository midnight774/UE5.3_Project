// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "JHAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJH_API AJHAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AJHAIController();

public:
	void RunAI();
	void StopAI();

	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;
	void SetEnableRunAI(bool bEnable);

public:
	FORCEINLINE void SetTargetPos(const FVector& InTargetPos) { TargetPos = InTargetPos; }
	FORCEINLINE FVector& GetTargetPos() { return TargetPos; }

protected:
	FVector TargetPos;
	bool IsEnableRunAI;


protected:
	TObjectPtr<class UBlackboardData> BlackBoardAsset;
	TObjectPtr<class UBehaviorTree> BehaviorTree;
};
