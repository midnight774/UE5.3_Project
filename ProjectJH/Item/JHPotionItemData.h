// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/JHItemDataAsset.h"
#include "JHPotionItemData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJH_API UJHPotionItemData : public UJHItemDataAsset
{
	GENERATED_BODY()

public:
	UJHPotionItemData();

public:
	FORCEINLINE const int32 GetHealHP() const { return HealHP; }
	FORCEINLINE const int32 GetHealMP() const { return HealMP; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemData)
	int32 HealHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ItemData)
	int32 HealMP;
	
};
