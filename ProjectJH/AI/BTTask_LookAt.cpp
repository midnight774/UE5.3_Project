// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_LookAt.h"
#include "AI/JHAIMacro.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/JHEnemyAIInterface.h"

UBTTask_LookAt::UBTTask_LookAt()
{
}

EBTNodeResult::Type UBTTask_LookAt::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();

	APawn* TargetPawn = Cast<APawn>(BBComp->GetValueAsObject(AI_BB_KEY_TARGETOBJ));

	if (TargetPawn)
	{
		FVector TargetPos = TargetPawn->GetActorLocation();
		FVector AIPos = OwnerPawn->GetActorLocation();
		FVector LookDir = TargetPos - AIPos;

		LookDir.Normalize();
		LookDir.Z = 0.0f;

		FRotator TargetRot = FRotationMatrix::MakeFromX(LookDir).Rotator();
		OwnerPawn->SetActorRotation(FMath::RInterpTo(OwnerPawn->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 90.0f));

		return Result;
	}

	return EBTNodeResult::Type::Failed;
}
