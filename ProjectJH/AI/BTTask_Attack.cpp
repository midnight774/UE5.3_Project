// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Attack.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Interface/JHEnemyAIInterface.h"
#include "AI/JHAIController.h"

UBTTask_Attack::UBTTask_Attack()
{
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* OwnerPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());

	if (nullptr == OwnerPawn)
	{
		return EBTNodeResult::Type::Failed;
	}

	IJHEnemyAIInterface* EnemyAI = Cast<IJHEnemyAIInterface>(OwnerPawn);

	if (nullptr == EnemyAI)
	{
		return EBTNodeResult::Type::Failed;
	}

	FAIAttackFinishedDelegate AttackEndDelegate;

	AttackEndDelegate.BindLambda(
		[&]()
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Type::Succeeded);
		}
	);

	EnemyAI->SetAttackFinishedDelegate(AttackEndDelegate);
	EnemyAI->AIAttack();

	return Result;
}
