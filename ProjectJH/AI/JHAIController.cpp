// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/JHAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "JHAIMacro.h"
#include "Character/JHCharacterEnemy.h"

AJHAIController::AJHAIController()
{
	ConstructorHelpers::FObjectFinder<UBehaviorTree> BTRef(TEXT("/Script/AIModule.BehaviorTree'/Game/ProectJH/AI/Enemy/Spider/BT_JHSpider.BT_JHSpider'"));

	if (BTRef.Object)
	{
		BehaviorTree = BTRef.Object;
	}

	ConstructorHelpers::FObjectFinder<UBlackboardData> BBRef(TEXT("/Script/AIModule.BlackboardData'/Game/ProectJH/AI/Enemy/Spider/BB_JHSpider.BB_JHSpider'"));

	if (BBRef.Object)
	{
		BlackBoardAsset = BBRef.Object;
	}
}

void AJHAIController::RunAI()
{
	UBlackboardComponent* BBPtr = Blackboard.Get();

	if (UseBlackboard(BlackBoardAsset, BBPtr))
	{
		FVector HomePos = GetPawn()->GetActorLocation();
		Blackboard->SetValueAsVector(AI_BB_KEY_HOMEPOS, HomePos);
		bool Result = RunBehaviorTree(BehaviorTree);

		ensure(Result);
	}
}

void AJHAIController::StopAI()
{
	UBehaviorTreeComponent* BTComp = Cast<UBehaviorTreeComponent>(BrainComponent);

	if (BTComp)
	{
		BTComp->StopTree(EBTStopMode::Safe);
	}
}

void AJHAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (IsEnableRunAI)
	{
		RunAI();
	}
}

void AJHAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AJHAIController::SetEnableRunAI(bool bEnable)
{
	if (bEnable == IsEnableRunAI)
	{
		return;
	}

	IsEnableRunAI = bEnable;

	if (IsEnableRunAI)
	{
		RunAI();
	}

	else
	{
		StopAI();
	}
}
