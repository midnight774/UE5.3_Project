// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_ExecuteAISkill.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/JHAISkillInterface.h"
#include "NavigationSystem.h"
#include "AI/JHAIController.h"
#include "AI/JHAIMacro.h"


UBTTask_ExecuteAISkill::UBTTask_ExecuteAISkill()
{
}

EBTNodeResult::Type UBTTask_ExecuteAISkill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* OwnerPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	check(OwnerPawn);

	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	check(BBComp);

	IJHAISkillInterface* AISkill = Cast<IJHAISkillInterface>(OwnerPawn);
	check(AISkill);

	AJHAIController* Controller = Cast<AJHAIController>(OwnerComp.GetAIOwner());
	check(Controller);

	FVector OriginPos = BBComp->GetValueAsVector(AI_BB_KEY_HOMEPOS);

	FAISkillFinishedDelegate EndDelegate;
	AISkill->ExecuteAISkill(0);

	EndDelegate.BindLambda(
		[&]()
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Type::Succeeded);
		}
	);

	AISkill->SetAISkillFinishedDelegate(EndDelegate);

	return EBTNodeResult::Type::InProgress;
}
