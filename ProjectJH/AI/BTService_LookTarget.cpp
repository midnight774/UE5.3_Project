// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_LookTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Interface/JHEnemyAIInterface.h"
#include "JHAIController.h"
#include "JHAIMacro.h"

void UBTService_LookTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* OwnerPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());

	if (nullptr == OwnerPawn)
	{
		return;
	}

	IJHEnemyAIInterface* EnemyAI = Cast<IJHEnemyAIInterface>(OwnerPawn);

	if (nullptr == EnemyAI)
	{
		return;
	}

	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();

	if (BBComp)
	{
		APawn* PlayerPawn = Cast<APawn>(BBComp->GetValueAsObject(AI_BB_KEY_TARGETOBJ));
		if (PlayerPawn)
		{
			FVector PlayerPos = PlayerPawn->GetActorLocation();

			EnemyAI->AILookAtTarget(PlayerPos);

		}
	}

}
