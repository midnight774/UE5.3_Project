// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_IsProcessingCombo.h"
#include "Interface/JHEnemyAIInterface.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/JHAIController.h"
#include "AI/JHAIMacro.h"

UBTDecorator_IsProcessingCombo::UBTDecorator_IsProcessingCombo()
{
}

bool UBTDecorator_IsProcessingCombo::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	APawn* OwnerPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());

	if (nullptr == OwnerPawn)
	{
		return false;
	}

	IJHEnemyAIInterface* EnemyAI = Cast<IJHEnemyAIInterface>(OwnerPawn);

	if (nullptr == EnemyAI)
	{
		return false;
	}

	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();

	if (nullptr == BBComp)
	{
		return false;
	}

	if (EnemyAI->IsAIAttackEnded())
	{
		return false;
	}

	return true;
}
