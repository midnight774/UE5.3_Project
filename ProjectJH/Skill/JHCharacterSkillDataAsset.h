// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "JHCharacterSkillDataAsset.generated.h"

/**
 * 
 */
UENUM()
enum class ESkillType : uint32
{
	Q,
	E,
	R
};

UCLASS()
class PROJECTJH_API UJHCharacterSkillDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UJHCharacterSkillDataAsset();


	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("SkillData", GetFName());
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillActionData)
	ESkillType SkillType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillActionData)
	TArray<TObjectPtr<class UParticleSystem>> ArrEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillActionData)
	TArray<FString> ArrEffectSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillActionData)
	TObjectPtr<class USoundClass> Sound;

};
