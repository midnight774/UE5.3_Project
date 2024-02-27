// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_InAttackDistance.h"
#include "Interface/JHEnemyAIInterface.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/JHAIController.h"
#include "AI/JHAIMacro.h"

UBTDecorator_InAttackDistance::UBTDecorator_InAttackDistance()
{
}

bool UBTDecorator_InAttackDistance::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
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

	AActor* PlayerActor = Cast<AActor>(BBComp->GetValueAsObject(AI_BB_KEY_TARGETOBJ));
	
	if (PlayerActor)
	{
		FVector TargetPos = PlayerActor->GetActorLocation();
		FVector OwnerPos = OwnerPawn->GetActorLocation();

		float AttackDist = EnemyAI->GetAttackDistance();

		FVector MoveDir = TargetPos - OwnerPos;
		MoveDir.Normalize();

		TargetPos -= AttackDist * MoveDir;

		BBComp->SetValueAsVector(AI_BB_KEY_TARGETPOS, TargetPos);
		float TargetDistance = FVector::Distance(OwnerPos, TargetPos);

		if (TargetDistance - AttackDist < KINDA_SMALL_NUMBER)
		{
			BBComp->SetValueAsBool(AI_BB_KEY_ISATTACKIING, true);
			return true;
		}
	}

	BBComp->SetValueAsBool(AI_BB_KEY_ISATTACKIING, false);

	return false;
}
