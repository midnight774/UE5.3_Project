// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_DetectPlayer.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/JHEnemyAIInterface.h"
#include "AI/JHAIController.h"
#include "CollisionQueryParams.h"
#include "AI/JHAIMacro.h"
#include "Collision/JHCollision.h"
#include "NavigationSystem.h"

UBTService_DetectPlayer::UBTService_DetectPlayer()
{
}

void UBTService_DetectPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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

	TArray<FOverlapResult> OutResults;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(OwnerPawn);

	const float DetectRange = EnemyAI->GetDetectDistance();

	const FVector Center = OwnerPawn->GetActorLocation();

	bool bDetected = GetWorld()->OverlapMultiByChannel(OutResults, Center, FQuat::Identity, COL_CHANNEL_ACTION_ENEMY, FCollisionShape::MakeSphere(DetectRange), Params);

	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();

	if (bDetected)
	{
		if (BBComp)
		{
			BBComp->SetValueAsObject(AI_BB_KEY_TARGETOBJ, OutResults[0].GetActor());
			AJHAIController* AIController = Cast<AJHAIController>(OwnerPawn->GetController());

			UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(OwnerPawn->GetWorld());

			FVector OriginPos = OutResults[0].GetActor()->GetActorLocation();
			FVector ActorPos = OwnerPawn->GetActorLocation();

			FVector Dir = OriginPos - ActorPos;
			Dir.Normalize();
			OriginPos -= Dir * (EnemyAI->GetAttackDistance() * 0.6f);

			FNavLocation TargetPos;

			if (NavSystem->GetRandomPointInNavigableRadius(OriginPos, 30.0f, TargetPos))
			{
				AIController->SetTargetPos(TargetPos.Location);
				BBComp->SetValueAsVector(AI_BB_KEY_TARGETPOS, TargetPos.Location);
			}

		}
	}

	else
	{
		if (BBComp)
		{
			BBComp->SetValueAsObject(AI_BB_KEY_TARGETOBJ, nullptr);
		}

	}

#if ENABLE_DRAW_DEBUG

	FColor DrawColor = (bDetected) ? FColor::Red : FColor::Green;

	DrawDebugSphere(GetWorld(), Center, DetectRange, 30, DrawColor, false, 0.2f);

#endif

}
