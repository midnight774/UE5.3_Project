// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JHSkillComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnChangedQCoolTimeDelegate, float /*CurrentCoolTime*/, uint8 /*IsCharged*/);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnChangedECoolTimeDelegate, float /*CurrentCoolTime*/, uint8 /*IsCharged*/);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnChangedRCoolTimeDelegate, float /*CurrentCoolTime*/, uint8 /*IsCharged*/);

USTRUCT()
struct FSkillEffects
{
	GENERATED_BODY()

	TArray<TObjectPtr<class UParticleSystemComponent>> Particles;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECTJH_API UJHSkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UJHSkillComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(VisibleAnywhere, Category = SkillInfo, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<APawn> OwnerPawn;

public:
	FORCEINLINE void SetOwner(APawn* InPawn) { OwnerPawn = InPawn; }

public:
	FOnChangedQCoolTimeDelegate OnQSkillCoolTimeChanged;
	FOnChangedECoolTimeDelegate OnESkillCoolTimeChanged;
	FOnChangedRCoolTimeDelegate OnRSkillCoolTimeChanged;

	FORCEINLINE bool IsEnableQSkill() { return bQSkillEnable; }
	FORCEINLINE bool IsEnableESkill() { return bESkillEnable; }
	FORCEINLINE bool IsEnableRSkill() { return bRSkillEnable; }

	FORCEINLINE void UseQSkill() { bQSkillEnable = false; }
	FORCEINLINE void UseESkill() { bESkillEnable = false; }
	FORCEINLINE void UseRSkill() { bRSkillEnable = false; }

	FORCEINLINE void SetQSkillCoolTime(float InMaxTime) { QCoolTimeMax = InMaxTime; }
	FORCEINLINE void SetESkillCoolTime(float InMaxTime) { ECoolTimeMax = InMaxTime; }
	FORCEINLINE void SetRSkillCoolTime(float InMaxTime) { RCoolTimeMax = InMaxTime; };

protected:
	UPROPERTY(EditAnywhere, Category = SkillInfo, Meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<class UJHCharacterSkillDataAsset>> ArrQSkillData;

	UPROPERTY(EditAnywhere, Category = SkillInfo, Meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<class UJHCharacterSkillDataAsset>> ArrESkillData;

	UPROPERTY(EditAnywhere, Category = SkillInfo, Meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<class UJHCharacterSkillDataAsset>> ArrRSkillData;

protected:

	UPROPERTY(EditAnywhere, Category = SkillEffectInfo, Meta = (AllowPrivateAccess = "true"))
	TArray<FSkillEffects> ArrQSkillEffect;

	UPROPERTY(EditAnywhere, Category = SkillEffectInfo, Meta = (AllowPrivateAccess = "true"))
	TArray<FSkillEffects> ArrESkillEffect;

	UPROPERTY(EditAnywhere, Category = SkillEffectInfo, Meta = (AllowPrivateAccess = "true"))
	TArray<FSkillEffects> ArrRSkillEffect;

public:
	void AddQSkillData(class UJHCharacterSkillDataAsset* QSkillData);
	void AddESkillData(class UJHCharacterSkillDataAsset* ESkillData);
	void AddRSkillData(class UJHCharacterSkillDataAsset* RSkillData);

	void AddQSkillEffectData(const TArray<TObjectPtr<class UParticleSystemComponent>>& Particles);
	void AddESkillEffectData(const TArray<TObjectPtr<class UParticleSystemComponent>>& Particles);
	void AddRSkillEffectData(const TArray<TObjectPtr<class UParticleSystemComponent>>& Particles);

	UPROPERTY(EditAnywhere, Category = SkillInfo, Meta = (AllowPrivateAccess = "true"))
	int32 QSkillIdx = 0;

	UPROPERTY(EditAnywhere, Category = SkillInfo, Meta = (AllowPrivateAccess = "true"))
	int32 ESkillIdx = 0;

	UPROPERTY(EditAnywhere, Category = SkillInfo, Meta = (AllowPrivateAccess = "true"))
	int32 RSkillIdx = 0;

public:
	void ExecuteQSkillData();
	void ExecuteESkillData();
	void ExecuteRSkillData();

protected:
	UPROPERTY(EditAnywhere, Category = SkillInfo, Meta = (AllowPrivateAccess = "true"))
	float QCoolTimeMax;

	UPROPERTY(EditAnywhere, Category = SkillInfo, Meta = (AllowPrivateAccess = "true"))
	float QCoolTime;

	UPROPERTY(EditAnywhere, Category = SkillInfo, Meta = (AllowPrivateAccess = "true"))
	float RCoolTimeMax;

	UPROPERTY(EditAnywhere, Category = SkillInfo, Meta = (AllowPrivateAccess = "true"))
	float RCoolTime;

	UPROPERTY(EditAnywhere, Category = SkillInfo, Meta = (AllowPrivateAccess = "true"))
	float ECoolTimeMax;

	UPROPERTY(EditAnywhere, Category = SkillInfo, Meta = (AllowPrivateAccess = "true"))
	float ECoolTime;

	UPROPERTY(EditAnywhere, Category = SkillInfo, Meta = (AllowPrivateAccess = "true"))
	uint8 bQSkillEnable : 1;

	UPROPERTY(EditAnywhere, Category = SkillInfo, Meta = (AllowPrivateAccess = "true"))
	uint8 bESkillEnable : 1;

	UPROPERTY(EditAnywhere, Category = SkillInfo, Meta = (AllowPrivateAccess = "true"))
	uint8 bRSkillEnable : 1;

protected:
	void UpdateQCoolTime(float DeltaTime);
	void UpdateECoolTime(float DeltaTime);
	void UpdateRCoolTime(float DeltaTime);

};
