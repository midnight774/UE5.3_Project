// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "InGameData/JHCharacterStat.h"
#include "JHCharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpZeroDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChangedDelegate, float /*CurrentHp*/);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMpChangedDelegate, float /*CurrentHp*/);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStatChangedDelegate, const FJHCharacterStat& /*BaseStat*/, const FJHCharacterStat& /*ModifierStat*/);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTJH_API UJHCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UJHCharacterStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	virtual void InitializeComponent() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FOnHpZeroDelegate OnHPZero;
	FOnHpChangedDelegate OnHPChanged;
	FOnMpChangedDelegate OnMPChanged;
	FOnStatChangedDelegate OnStatChanged;

	FORCEINLINE	const float GetMaxHP() const { return MaxHP; }
	FORCEINLINE	const float GetMaxMP() const { return MaxMP; }
	FORCEINLINE	const float GetCurrentHP() const { return CurrentHP; }
	FORCEINLINE	const float GetCurrentMP() const { return CurrentMP; }
	FORCEINLINE	const float GetAttack() const { return Attack; }
	FORCEINLINE	const float GetAttackRange() const { return AttackRange; }
	FORCEINLINE	const float GetAttackSpeed() const { return AttackSpeed; }
	FORCEINLINE	const float GetDefence() const { return Defence; }
	FORCEINLINE	const float GetMoveSpeed() const { return MoveSpeed; }

	FORCEINLINE void SetAttack(float InAttack) { Attack = InAttack; }

	float ApplyDamage(float InDamage);
	void HealHP(float InHeal);
	void HealMP(float InHeal);
	void UseMP(float InMPCost);

	void SetCharacterStatByName(const FString& InName);
	void SetCharacterStatByName(const FName& InName);

	void FindCharacterStat(const FName& InName);
	void SetCharacterStat(const struct FJHCharacterStat* InStat);
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStat)
	FName CharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStat)
	float MaxHP;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStat)
	float CurrentHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStat)
	float MaxMP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStat)
	float CurrentMP;;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStat)
	float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStat)
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStat)
	float AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStat)
	float Defence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStat)
	float MoveSpeed;
};
