// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/JHCharacterBase.h"
#include "Engine/StreamableManager.h"
#include "Interface/JHEnemyAIInterface.h"
#include "Interface/JHWorldWidgetInterface.h"
#include "JHCharacterEnemy.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJH_API AJHCharacterEnemy : public AJHCharacterBase, public IJHEnemyAIInterface, public IJHWorldWidgetInterface
{
	GENERATED_BODY()
	
public:
	AJHCharacterEnemy();

protected:

	virtual void PostInitializeComponents() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void ProcessComboAttack();
	virtual void AttackFinish() override;
	virtual void SetDead() override;
	virtual void DestroyCallback() override;

protected:

	virtual bool IsRageOn() override;

	UPROPERTY()
	float DamageAccumulate = 0.0f;

	UPROPERTY()
	float RageRatio = 0.3f;

	bool bIsRage = false;

protected:
	UPROPERTY(Config)
	FSoftObjectPath  EnemyMeshPath;

	TSharedPtr<FStreamableHandle> EnemyMeshHandle;

	void IsCompletedLoadEnemyMesh();

//AI Interface Functions
public:
	virtual float GetPatrolDistance() override;
	virtual float GetDetectDistance() override;
	virtual float GetAttackDistance() override;
	virtual float GetTaskChangeTime() override;

	virtual void AIAttack() override;
	virtual void AILookAtTarget(const FVector& TargetPos) override;
	virtual void AIMoveToTarget() override;
	virtual bool IsAIAttackEnded() override;
	virtual void SetAttackFinishedDelegate(const FAIAttackFinishedDelegate& Delegate) override;
	virtual void ActivateAI(bool bActive) override;
	virtual void SetAILevelStart() override;

	bool IsIntroStarted = false;

//AI Variables;
protected:

	UPROPERTY(EditAnywhere, Category = AIValues)
	float PatrolDistance;

	UPROPERTY(EditAnywhere, Category = AIValues)
	float DetectDistance;

	UPROPERTY(EditAnywhere, Category = AIValues)
	float AttackDistance;

	UPROPERTY(EditAnywhere, Category = AIValues)
	float TaskChangeTime;

	FAIAttackFinishedDelegate AIAttackFinDelegate;

	bool AutoActivateAI;

	bool bDissolveEnable = true;

public:
	virtual void SetupWorldWidget(class UJHUserWidget* WorldWidget) override;
	virtual void SetupBossWidget(class UJHBossWidget* InBossWidget);

protected:

	UPROPERTY()
	TObjectPtr<class UJHWidgetComponent> WidgetComponent;
};
