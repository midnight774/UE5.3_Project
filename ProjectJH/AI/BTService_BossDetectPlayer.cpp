// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_BossDetectPlayer.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/JHEnemyAIInterface.h"
#include "AI/JHAIController.h"
#include "CollisionQueryParams.h"
#include "AI/JHAIMacro.h"
#include "Collision/JHCollision.h"
#include "NavigationSystem.h"

void UBTService_BossDetectPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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

	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();

	if (BBComp)
	{

		bool IsRage = EnemyAI->IsRageOn();
		BBComp->SetValueAsBool(AI_BB_KEY_ISRAGE, IsRage);

		if (PlayerPawn)
		{
			BBComp->SetValueAsObject(AI_BB_KEY_TARGETOBJ, PlayerPawn);
			AJHAIController* AIController = Cast<AJHAIController>(OwnerPawn->GetController());

			UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(OwnerPawn->GetWorld());

			FVector OriginPos = PlayerPawn->GetActorLocation();
			FNavLocation TargetPos;

			if (NavSystem->GetRandomPointInNavigableRadius(OriginPos, 30.0f, TargetPos))
			{
				AIController->SetTargetPos(TargetPos.Location);
				BBComp->SetValueAsVector(AI_BB_KEY_TARGETPOS, TargetPos.Location);
			}
		}

		else
		{
			BBComp->SetValueAsObject(AI_BB_KEY_TARGETOBJ, nullptr);
		}
	}


}
