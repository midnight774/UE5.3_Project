// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/JHCharacterEnemy.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Collision/JHCollision.h"
#include "Engine/AssetManager.h"
#include "AI/JHAIController.h"
#include "Component/JHDissolveComponent.h"
#include "UI/JHUserWidget.h"
#include "UI/JHWidgetComponent.h"
#include "Item/JHFieldItemActor.h"
#include "Animation/JHAnimInstance.h"

AJHCharacterEnemy::AJHCharacterEnemy() : PatrolDistance(50.0f),
										 DetectDistance(100.0f),
										 AttackDistance(30.0f),
										 TaskChangeTime(2.0f)

{
	GetCapsuleComponent()->SetCollisionProfileName(COL_PROFILE_CAPSULE_ENEMY);

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_NavWalking);
	AutoActivateAI = true;
}

void AJHCharacterEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	FSimpleDelegate LoadDelegate = FStreamableDelegate::CreateUObject(this, &AJHCharacterEnemy::IsCompletedLoadEnemyMesh);
	EnemyMeshHandle = UAssetManager::GetStreamableManager().RequestAsyncLoad(EnemyMeshPath, LoadDelegate);
}

void AJHCharacterEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (AutoActivateAI)
	{
		ActivateAI(true);
	}
	
}

void AJHCharacterEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AJHCharacterEnemy::ProcessComboAttack()
{
	Super::ProcessComboAttack();
}

void AJHCharacterEnemy::AttackFinish()
{
	Super::AttackFinish();

	AIAttackFinDelegate.ExecuteIfBound();
}

void AJHCharacterEnemy::SetDead()
{
	AJHAIController* AIController = Cast<AJHAIController>(GetController());

	if (AIController)
	{
		AIController->StopAI();
	}

	Super::SetDead();

	if (bDissolveEnable)
	{
		UJHDissolveComponent* DsvComp = NewObject<UJHDissolveComponent>(this);

		DsvComp->SetDissolveSpeed(0.2f);
		DsvComp->SetTargetSkeletal(GetMesh());
		DsvComp->StartDissolve();
		DsvComp->RegisterComponent();
	}
}

void AJHCharacterEnemy::DestroyCallback()
{
	AJHFieldItemActor* DropItem = GetWorld()->SpawnActor<AJHFieldItemActor>();
	DropItem->SetActorLocation(GetActorLocation());
	DropItem->SetGroundLocation();
}

bool AJHCharacterEnemy::IsRageOn()
{
	return bIsRage;
}

void AJHCharacterEnemy::IsCompletedLoadEnemyMesh()
{
	if (EnemyMeshHandle.IsValid())
	{
		USkeletalMesh* EnemyMesh = Cast<USkeletalMesh>(EnemyMeshHandle->GetLoadedAsset());

		if (EnemyMesh)
		{
			GetMesh()->SetSkeletalMesh(EnemyMesh);
		}

		EnemyMeshHandle->ReleaseHandle();
	}

}

float AJHCharacterEnemy::GetPatrolDistance()
{
	return PatrolDistance;
}

float AJHCharacterEnemy::GetDetectDistance()
{
	return DetectDistance;
}

float AJHCharacterEnemy::GetAttackDistance()
{
	return AttackDistance;
}

float AJHCharacterEnemy::GetTaskChangeTime()
{
	return TaskChangeTime;
}

void AJHCharacterEnemy::AIAttack()
{
	ProcessComboAttack();
}

void AJHCharacterEnemy::AILookAtTarget(const FVector& TargetPos)
{
	LookAt(TargetPos);
}

void AJHCharacterEnemy::AIMoveToTarget()
{
}

bool AJHCharacterEnemy::IsAIAttackEnded()
{
	if (CurrentComboCount < ComboCountMax)
	{
		return false;
	}

	return true;
}

void AJHCharacterEnemy::SetAttackFinishedDelegate(const FAIAttackFinishedDelegate& Delegate)
{
	AIAttackFinDelegate = Delegate;
}

void AJHCharacterEnemy::ActivateAI(bool bActive)
{
	AJHAIController* AIController = Cast<AJHAIController>(GetController());

	if (AIController)
	{
		AIController->SetEnableRunAI(bActive);
	}
}

void AJHCharacterEnemy::SetAILevelStart()
{
	
}

void AJHCharacterEnemy::SetupWorldWidget(UJHUserWidget* WorldWidget)
{
	WidgetComponent->SetWidget(WorldWidget);
	//스탯 연동 해야함 ㅇㅇ
}

void AJHCharacterEnemy::SetupBossWidget(UJHBossWidget* InBossWidget)
{
}
