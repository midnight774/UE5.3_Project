// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_ProcessRage.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/JHAISkillInterface.h"
#include "NavigationSystem.h"
#include "AI/JHAIController.h"
#include "AI/JHAIMacro.h"
#include "Interface/JHEnemyAIInterface.h"

UBTTask_ProcessRage::UBTTask_ProcessRage()
{
}

EBTNodeResult::Type UBTTask_ProcessRage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* OwnerPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	check(OwnerPawn);

	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	check(BBComp);

	IJHAISkillInterface* AISkill = Cast<IJHAISkillInterface>(OwnerPawn);
	check(AISkill);

	IJHEnemyAIInterface* AIEnemy = Cast<IJHEnemyAIInterface>(OwnerPawn);
	check(AIEnemy);

	AJHAIController* Controller = Cast<AJHAIController>(OwnerComp.GetAIOwner());
	check(Controller);

	FAISkillFinishedDelegate EndDelegate;
	AISkill->ProcessRageSkill();

	EndDelegate.BindLambda
	(
		[&]()
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Type::Succeeded);
		}
	);

	AIEnemy->SetAttackFinishedDelegate(EndDelegate);

	return EBTNodeResult::Type::InProgress;
}
