// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/JHAIController.h"
#include "JHSevarogAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJH_API AJHSevarogAIController : public AJHAIController
{
	GENERATED_BODY()

public:
	AJHSevarogAIController();

public:
	void RunAI();
	void StopAI();

	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;
	virtual void UseSkill();

	FORCEINLINE const int32 GetSkillCnt() const { return SkillCnt; }
	FORCEINLINE void SetSkillCnt(const int32 InCnt) { SkillCnt = InCnt; }

protected:
	int32 SkillCnt;
	
};
