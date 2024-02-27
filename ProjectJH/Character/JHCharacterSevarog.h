// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/JHCharacterEnemy.h"
#include "Interface/JHProjectileAttackInterface.h"
#include "Interface/JHAISkillInterface.h"
#include "JHCharacterSevarog.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJH_API AJHCharacterSevarog : public AJHCharacterEnemy, public IJHProjectileAttackInterface, public IJHAISkillInterface
{
	GENERATED_BODY()
	
public:
	AJHCharacterSevarog();

protected:

	virtual void PostInitializeComponents() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void SetLevelStart();

	UFUNCTION(BlueprintCallable)
	void SetActivateAI();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void ProcessComboAttack()	override;
	virtual void AttackFinish()			override;
	virtual void SetDead()				override;
public:
	float FadeOut = 0.0f;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	virtual class AJHActorProjectile* SpawnProjectile(const FVector& MoveDir, const FVector& SpawnPos, float MoveSpeed = 100.0f, float MoveTime = 2.0f) override;
	virtual void StartFireMontage()	 override;
	virtual void AdjustFirePos()	 override;
	virtual void FireProjectile()	 override;

	virtual class AJHStormActor* SpawnStorm(const FVector& SpawnPos, float MoveSpeed = 100.0f, float MoveTime = 2.0f);

	//Anim Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ComboAttackInfo, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> CastMontage;

	UPROPERTY(EditAnywhere, Category = ComboAttackInfo, Meta = (AllowPrivateAccess = "true"))
	TArray<FSkillMontages> ArrSkillMontage;

	UPROPERTY(EditAnywhere, Category = ComboAttackInfo, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage>  RageSkillMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ComboAttackInfo, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> IntroMontage;

	bool IsEnableProjSkill = false;
	float CastTime = 0.0f;
	const float CastTimeMax = 0.5f;
	int32 CurrentParticleIdx = 0;

	void SpawnCastProjParticle(float DeltaTime);

	bool IsEnableProjFire = false;
	float FireTime = 0.0f;
	const float FireTimeMax = 0.5f;
	int32 CurrentFireIdx = 0;

	void FireProjectilesTick(float DeltaTime);

	void PlayLevelStartMontage();
	bool IsLevelStarted = false;

protected:
	UPROPERTY()
	TArray<TObjectPtr<class UParticleSystemComponent>> ArrProjStartParticle;

	UPROPERTY()
	TObjectPtr<UParticleSystem> ProjCastParticle;

	UPROPERTY()
	TObjectPtr<UParticleSystem> ProjHitParticle;

	UPROPERTY()
	TObjectPtr<UParticleSystem> ProjBodyParticle;

	//SkillSection
protected:
	virtual void ExecuteAISkill(const int32 SkillIdx) override;
	virtual void ProcessSkill() override;
	virtual void ProcessRageSkill() override;
	virtual void SkillFinished() override;
	virtual void SetAISkillFinishedDelegate(const FAISkillFinishedDelegate& Delegate);
	virtual void SetCharacterPause() override;
	virtual void ActivateAI(bool bActive) override;

	void TeleportOn();
	void FinishTeleport(); 

	void ProcessNextSkillMontage(FSkillMontages& SkillMontages);

	FAISkillFinishedDelegate OnSkillFinishedDelegate;

	int32 CurrentSkillIdx;

	float TeleportTime = 0.0f;
	float TelportTimeMax = 1.5f;
	bool IsProcessingTeleport = false;

public:
	virtual void SetupBossWidget(class UJHBossWidget* InBossWidget) override;
};
