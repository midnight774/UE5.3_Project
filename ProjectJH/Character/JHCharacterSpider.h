// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/JHCharacterEnemy.h"
#include "JHCharacterSpider.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJH_API AJHCharacterSpider : public AJHCharacterEnemy
{
	GENERATED_BODY()

public:
	AJHCharacterSpider();

protected:

	virtual void PostInitializeComponents() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void ProcessComboAttack() override;
	virtual void AttackFinish() override;
	virtual void SetDead() override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	void ComputeInclineDegree();
};
