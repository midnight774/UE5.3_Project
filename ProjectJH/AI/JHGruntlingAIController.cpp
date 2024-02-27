// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/JHGruntlingAIController.h"

AJHGruntlingAIController::AJHGruntlingAIController()	: SkillCoolTime(0.0f)
														, SkillCoolTimeMax(4.0f)
														, bSkillEnable(true)
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> GruntBTRef(TEXT("/Script/AIModule.BehaviorTree'/Game/ProectJH/AI/Enemy/Gruntling/BT_JHGruntling.BT_JHGruntling'"));

	if (GruntBTRef.Object)
	{
		BehaviorTree = GruntBTRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBlackboardData> GruntBBRef(TEXT("/Script/AIModule.BlackboardData'/Game/ProectJH/AI/Enemy/Gruntling/BB_JHGruntling.BB_JHGruntling'"));

	if (GruntBBRef.Object)
	{
		BlackBoardAsset = GruntBBRef.Object;
	}
}

void AJHGruntlingAIController::RunAI()
{
	Super::RunAI();
}

void AJHGruntlingAIController::StopAI()
{
	Super::StopAI();
}

void AJHGruntlingAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AJHGruntlingAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bSkillEnable)
	{
		SkillCoolTime += DeltaTime;

		if (SkillCoolTimeMax - SkillCoolTime < KINDA_SMALL_NUMBER)
		{
			SkillCoolTime = 0.0f;
			bSkillEnable = true;
		}
	}
	
}

void AJHGruntlingAIController::UseSkill()
{
	bSkillEnable = false;
}
