// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_DecidePatrolPos.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/JHEnemyAIInterface.h"
#include "NavigationSystem.h"
#include "AI/JHAIController.h"
#include "AI/JHAIMacro.h"

UBTTask_DecidePatrolPos::UBTTask_DecidePatrolPos()
{
}

EBTNodeResult::Type UBTTask_DecidePatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* OwnerPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());

	if (nullptr == OwnerPawn)
	{
		return EBTNodeResult::Type::Failed;
	}

	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();

	if (nullptr == BBComp)
	{
		return EBTNodeResult::Type::Failed;
	}

	IJHEnemyAIInterface* EnemyAI = Cast<IJHEnemyAIInterface>(OwnerPawn);

	if (nullptr == EnemyAI)
	{
		return EBTNodeResult::Type::Failed;
	}

	float PatrolDist = EnemyAI->GetPatrolDistance();
	
	AJHAIController* Controller = Cast<AJHAIController>(OwnerComp.GetAIOwner());

	if (nullptr == Controller)
	{
		return EBTNodeResult::Type::Failed;
	}

	FVector OriginPos = BBComp->GetValueAsVector(AI_BB_KEY_HOMEPOS);
	
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(OwnerPawn->GetWorld());

	FNavLocation PatrolPos;

	if (NavSystem->GetRandomPointInNavigableRadius(OriginPos, PatrolDist, PatrolPos))
	{
		BBComp->SetValueAsVector(AI_BB_KEY_PATROLPOS, PatrolPos.Location);
		return EBTNodeResult::Type::Succeeded;
	}

	return EBTNodeResult::Type::Failed;
}
