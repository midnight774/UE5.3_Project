// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_SetRandSkillNum.h"
#include "AI/JHAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/JHAIMacro.h"

UBTDecorator_SetRandSkillNum::UBTDecorator_SetRandSkillNum()
{
}

bool UBTDecorator_SetRandSkillNum::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	APawn* OwnerPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	check(OwnerPawn);

	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	check(BBComp);

	float fRandom = FMath::RandRange(0.00f, 1.00f);
	int32 iRandom = (int32)(fRandom * 100);

	BBComp->SetValueAsInt(AI_BB_KEY_SKILL_RAND, iRandom);

	return true;
}
