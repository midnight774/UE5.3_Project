// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/JHAnimationAttackInterface.h"
#include "Interface/JHAnimationDefenceInterface.h"
#include "JHCharacterBase.generated.h"

UCLASS()
class PROJECTJH_API AJHCharacterBase : public ACharacter, public IJHAnimationAttackInterface, public IJHAnimationDefenceInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AJHCharacterBase();

protected:
	virtual void PostInitializeComponents() override;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DefaultAttackTick(float DeltaTime);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	FORCEINLINE class UAnimMontage* GetLevelStartMontage() { return LevelStartMontage; }

	//Action Section
protected:
	virtual void ProcessComboAttack();
	virtual void AttackFinish() override;
	virtual void SetDead();
	virtual void DestroyCallback();

	void LookAt(const FVector& TargetPos);
	void MoveTo(const FVector& TargetPos);
	void AutoMove(float DeltaTime);
	void PlayDeadAnimation();

	FVector AutoMoveTargetPos;
	bool IsAutoMoving;

	bool IsDead;

	float DeadDelayTime;
	float DeadDelayTimeMax;
	float HitAngle;

	FTimerHandle SlowTimeHandle;
	float SlowTime;
	float SlowTimeMax;

	bool IsTargetLooking;
	FVector LookTargetPos;

	FORCEINLINE void SetLookTarget(const FVector& InLookPos) { LookTargetPos = InLookPos; }

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HitInfo)
	bool IsHitted;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HitInfo)
	float HitTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = HitInfo)
	float HitTimeMax;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ComboAttackInfo, Meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<class UAnimMontage>> ArrAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ComboAttackInfo, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> AttackEndMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ComboAttackInfo, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> DeadMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ComboAttackInfo, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> LevelStartMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ComboAttackInfo, Meta = (AllowPrivateAccess = "true"))
	int32 CurrentComboCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ComboAttackInfo, Meta = (AllowPrivateAccess = "true"))
	int32 ComboCountMax = 4;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ComboAttackInfo, Meta = (AllowPrivateAccess = "true"))
	uint8 IsPrecessCombo = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ComboAttackInfo, Meta = (AllowPrivateAccess = "true"))
	float ComboTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ComboAttackInfo, Meta = (AllowPrivateAccess = "true"))
	float NextComboEnableTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ComboAttackInfo, Meta = (AllowPrivateAccess = "true"))
	float ComboTimeMax = 1.5f;

//Stat Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	FString CharacterName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UJHCharacterStatComponent> StatComponent;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	FORCEINLINE const FString& GetCharacterName() const { return CharacterName; }

	//Collision Section
public:
	virtual void AttackHitCheck() override;
	virtual void HitSucceededCallback();

	//Defence Section
public:
	virtual void SetDefenceEnable(bool Enable) override;
	virtual bool IsDefenceSucceeded() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SkillAnimMonage, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UParticleSystemComponent> DefenceEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SkillInfo, Meta = (AllowPrivateAccess = "true"))
	uint8 bIsDefending : 1;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Effect, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystem> HitParticleBase;
};
