// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "JHItemDataAsset.generated.h"

/**
 * 
 */

UENUM()
enum class EItemType : uint32
{
	Potion = 0,
	BuffScroll,
	End
};

UCLASS()
class PROJECTJH_API UJHItemDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UJHItemDataAsset();

	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("JHItemData", GetFName());
	}

public:
	FORCEINLINE const EItemType GetItemType() const { return ItemType; }
	FORCEINLINE const FName& GetItemName() const { return ItemName; }
	FORCEINLINE UTexture2D* GetIconTexture() { return ItemImageTex; }
	FORCEINLINE UStaticMesh* GetItemMesh() { return ItemMesh; }
	FORCEINLINE const int32 GetItemCnt() { return ItemCnt; }
	FORCEINLINE void SetItemCnt(const int32 InCnt) { ItemCnt = InCnt; }
	FORCEINLINE void PlusItemCnt() { ++ItemCnt; };
	FORCEINLINE void MinusItemCnt() { --ItemCnt; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillActionData)
	FName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillActionData)
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillActionData)
	int32 ItemCnt = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillActionData)
	TObjectPtr<UTexture2D> ItemImageTex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillActionData)
	TObjectPtr<class UStaticMesh> ItemMesh;
};
