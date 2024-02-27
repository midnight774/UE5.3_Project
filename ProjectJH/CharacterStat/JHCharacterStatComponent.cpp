// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/JHCharacterStatComponent.h"
#include "InGameData/JHDataManager.h"

// Sets default values for this component's properties
UJHCharacterStatComponent::UJHCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UJHCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UJHCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

}


// Called every frame
void UJHCharacterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UJHCharacterStatComponent::ApplyDamage(float InDamage)
{
	float ResultDamage = FMath::Max(1.0f, InDamage - Defence);
	CurrentHP = FMath::Max(0.0f, CurrentHP - ResultDamage);

	if (CurrentHP < KINDA_SMALL_NUMBER)
	{
		OnHPZero.Broadcast();
	}

	OnHPChanged.Broadcast(CurrentHP);

	return ResultDamage;
}

void UJHCharacterStatComponent::HealHP(float InHeal)
{
	CurrentHP = FMath::Clamp(CurrentHP + InHeal, 0.0f, MaxHP);

	OnHPChanged.Broadcast(CurrentHP);
}

void UJHCharacterStatComponent::HealMP(float InHeal)
{
	CurrentMP = FMath::Clamp(CurrentMP + InHeal, 0.0f, MaxMP);

	OnMPChanged.Broadcast(CurrentMP);
}

void UJHCharacterStatComponent::UseMP(float InMPCost)
{
	CurrentMP = FMath::Clamp(CurrentMP - InMPCost, 0.0f, MaxMP);

	OnMPChanged.Broadcast(CurrentMP);
}

void UJHCharacterStatComponent::SetCharacterStatByName(const FString& InName)
{
	CharacterName = FName(InName);

	FindCharacterStat(CharacterName);
}

void UJHCharacterStatComponent::SetCharacterStatByName(const FName& InName)
{
	CharacterName = InName;

	FindCharacterStat(CharacterName);
}

void UJHCharacterStatComponent::FindCharacterStat(const FName& InName)
{
	UJHDataManager* DataManager = UJHDataManager::GetInst();
	const FJHCharacterStat* Stat = DataManager->FindCharacterStat(InName);
	
	if (Stat)
	{
		SetCharacterStat(Stat);
	}

}

void UJHCharacterStatComponent::SetCharacterStat(const FJHCharacterStat* InStat)
{
	MaxHP = InStat->MaxHP;
	CurrentHP = MaxHP;

	MaxMP = InStat->MaxMP;
	CurrentMP = MaxMP;

	Attack = InStat->Attack;

	AttackRange = InStat->AttackRange;
	AttackSpeed = InStat->AttackSpeed;

	Defence = InStat->Defence;
	MoveSpeed = InStat->MoveSpeed;
}
