// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/JHCharacterEnemy.h"
#include "Interface/JHProjectileAttackInterface.h"
#include "JHCharacterGruntling.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJH_API AJHCharacterGruntling : public AJHCharacterEnemy, public IJHProjectileAttackInterface
{
	GENERATED_BODY()

public:
	AJHCharacterGruntling();

protected:

	virtual void PostInitializeComponents() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void ProcessComboAttack()	override;
	virtual void AttackFinish()			override;
	virtual void SetDead()				override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;


protected:
	UPROPERTY(Config)
	FSoftObjectPath  WeaponMeshPath;

	TSharedPtr<FStreamableHandle> WeaponMeshHandle;

	void IsCompletedLoadWeaponMesh();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SkillAnimMonage, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> AttackRangeMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SkillEffect, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystem> AttackRangeBodyParticle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SkillEffect, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystem> AttackRangeHitParticle;

	//Projectile Section
	virtual class AJHActorProjectile* SpawnProjectile(const FVector& MoveDir, const FVector& SpawnPos, float MoveSpeed = 100.0f, float MoveTime = 2.0f);
	virtual void StartFireMontage() override;
	virtual void AdjustFirePos() override;
	virtual void FireProjectile() override;
};
