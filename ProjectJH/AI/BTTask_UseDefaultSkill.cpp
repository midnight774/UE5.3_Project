// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_UseDefaultSkill.h"
#include "Interface/JHProjectileAttackInterface.h"
#include "AI/JHGruntlingAIController.h"
#include "Interface/JHEnemyAIInterface.h"

UBTTask_UseDefaultSkill::UBTTask_UseDefaultSkill()
{
}

EBTNodeResult::Type UBTTask_UseDefaultSkill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* OwnerPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());

	if (nullptr == OwnerPawn)
	{
		return EBTNodeResult::Type::Failed;
	}

	IJHEnemyAIInterface* EnemyAI = Cast<IJHEnemyAIInterface>(OwnerPawn);
	IJHProjectileAttackInterface* ProjectileAttack = Cast<IJHProjectileAttackInterface>(OwnerPawn);

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
	ProjectileAttack->StartFireMontage();

	return EBTNodeResult::Type::InProgress;
}
