// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/JHSevarogAIController.h"

AJHSevarogAIController::AJHSevarogAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> SevarogBTRef(TEXT("/Script/AIModule.BehaviorTree'/Game/ProectJH/AI/Enemy/Sevarog/BT_JHSevarog.BT_JHSevarog'"));

	if (SevarogBTRef.Object)
	{
		BehaviorTree = SevarogBTRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBlackboardData> SevarogBBRef(TEXT("/Script/AIModule.BlackboardData'/Game/ProectJH/AI/Enemy/Sevarog/BB_JHSevrog.BB_JHSevrog'"));

	if (SevarogBBRef.Object)
	{
		BlackBoardAsset = SevarogBBRef.Object;
	}

	IsEnableRunAI = false;
}

void AJHSevarogAIController::RunAI()
{
	Super::RunAI();
}

void AJHSevarogAIController::StopAI()
{
	Super::StopAI();
}

void AJHSevarogAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AJHSevarogAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJHSevarogAIController::UseSkill()
{
}
