// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/JHSkillComponent.h"
#include "Skill/JHCharacterSkillDataAsset.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values for this component's properties
UJHSkillComponent::UJHSkillComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UJHSkillComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	bQSkillEnable = true;
	bESkillEnable = true;
	bRSkillEnable = true;

}


// Called every frame
void UJHSkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (!bQSkillEnable)
	{
		UpdateQCoolTime(DeltaTime);
	}

	if (!bESkillEnable)
	{
		UpdateECoolTime(DeltaTime);
	}

	if (!bRSkillEnable)
	{
		UpdateRCoolTime(DeltaTime);
	}
}
void UJHSkillComponent::AddQSkillData(UJHCharacterSkillDataAsset* QSkillData)
{
	ArrQSkillData.Add(QSkillData);
}
void UJHSkillComponent::AddESkillData(UJHCharacterSkillDataAsset* ESkillData)
{
	ArrESkillData.Add(ESkillData);
}
void UJHSkillComponent::AddRSkillData(UJHCharacterSkillDataAsset* RSkillData)
{
	ArrRSkillData.Add(RSkillData);
}

void UJHSkillComponent::AddQSkillEffectData(const TArray<TObjectPtr<class UParticleSystemComponent>>& Particles)
{
	FSkillEffects SkillDatas;
	SkillDatas.Particles = Particles;

	ArrQSkillEffect.Add(SkillDatas);
	
}

void UJHSkillComponent::AddESkillEffectData(const TArray<TObjectPtr<class UParticleSystemComponent>>& Particles)
{
	FSkillEffects SkillDatas;
	SkillDatas.Particles = Particles;

	ArrESkillEffect.Add(SkillDatas);
}

void UJHSkillComponent::AddRSkillEffectData(const TArray<TObjectPtr<class UParticleSystemComponent>>& Particles)
{
	FSkillEffects SkillDatas;
	SkillDatas.Particles = Particles;

	ArrRSkillEffect.Add(SkillDatas);
}

void UJHSkillComponent::ExecuteQSkillData()
{
	if (ArrQSkillEffect.IsValidIndex(ESkillIdx))
	{
		for (UParticleSystemComponent* Particle : ArrQSkillEffect[ESkillIdx].Particles)
		{
			Particle->Activate(true);
		}

		++ESkillIdx;

		if (ESkillIdx >= ArrQSkillEffect.Num())
		{
			ESkillIdx = 0;
		}
	}

	else
	{
		ESkillIdx = 0;
	}

}

void UJHSkillComponent::ExecuteESkillData()
{
	if (ArrESkillEffect.IsValidIndex(ESkillIdx))
	{
		for (UParticleSystemComponent* Particle : ArrESkillEffect[ESkillIdx].Particles)
		{
			Particle->Activate(true);
		}

		++ESkillIdx;

		if (ESkillIdx >= ArrESkillEffect.Num())
		{
			ESkillIdx = 0;
		}
	}

	else
	{
		ESkillIdx = 0;
	}
}

void UJHSkillComponent::ExecuteRSkillData()
{
	if (ArrRSkillEffect.IsValidIndex(RSkillIdx))
	{
		for (UParticleSystemComponent* Particle : ArrRSkillEffect[RSkillIdx].Particles)
		{	
			Particle->Activate(true);
		}

		++RSkillIdx;

		if(RSkillIdx >= ArrRSkillEffect.Num())
		{
			RSkillIdx = 0;
		}
	}

	else
	{
		RSkillIdx = 0;
	}
}
void UJHSkillComponent::UpdateQCoolTime(float DeltaTime)
{
	QCoolTime += DeltaTime;

	bool IsCharged = false;

	if (QCoolTimeMax - QCoolTime < KINDA_SMALL_NUMBER)
	{
		QCoolTime = 0.0f;
		bQSkillEnable = true;
		IsCharged = true;
	}

	OnQSkillCoolTimeChanged.Broadcast(QCoolTimeMax - QCoolTime, IsCharged);
}

void UJHSkillComponent::UpdateECoolTime(float DeltaTime)
{
	ECoolTime += DeltaTime;

	bool IsCharged = false;

	if (ECoolTimeMax - ECoolTime < KINDA_SMALL_NUMBER)
	{
		ECoolTime = 0.0f;
		bESkillEnable = true;
		IsCharged = true;
	}

	OnESkillCoolTimeChanged.Broadcast(ECoolTimeMax - ECoolTime, IsCharged);
}

void UJHSkillComponent::UpdateRCoolTime(float DeltaTime)
{
	RCoolTime += DeltaTime;

	bool IsCharged = false;

	if (RCoolTimeMax - RCoolTime < KINDA_SMALL_NUMBER)
	{
		RCoolTime = 0.0f;
		bRSkillEnable = true;
		IsCharged = true;
	}

	OnRSkillCoolTimeChanged.Broadcast(RCoolTimeMax - RCoolTime, IsCharged);
}