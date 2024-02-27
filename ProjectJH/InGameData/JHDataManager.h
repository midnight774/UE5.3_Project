// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "JHCharacterStat.h"
#include "JHDataManager.generated.h"

USTRUCT()
struct FItemSaveData
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<class UJHItemDataAsset> Item;

	int32 ItemCnt;
};

DECLARE_LOG_CATEGORY_EXTERN(LogJHDataManager, Error, All);

/**
 * 
 */
UCLASS()
class PROJECTJH_API UJHDataManager : public UObject
{
	GENERATED_BODY()
	
public:
	UJHDataManager();

	static UJHDataManager* GetInst();

	//Character Stat Data Section
public:
	const FJHCharacterStat* FindCharacterStat(const FName& InName);

	FORCEINLINE bool IsExistLoadableData() { return IsSaved; }

	void SaveCharacterStat(class UJHCharacterStatComponent* StatComponent);
	void LoadCharacterStat(class UJHCharacterStatComponent* StatComponent);

	void SaveInventoryData(class UJHItemDataAsset* InItem, int32 Idx, int32 Cnt);
	void SaveQuickSlotData(class UJHItemDataAsset* InItem, int32 Idx, int32 Cnt);

	void LoadInventoryData(class UJHInventoryComponent* Inventory);
	void LoadQuickSlotData(class UJHQuickSlotComponent* Quickslot);

	void SaveCharacterItemData(class UJHInventoryComponent* Inventory, class UJHQuickSlotComponent* Quickslot);
	void LoadCharacterItemData(class UJHInventoryComponent* OutInventory, class UJHQuickSlotComponent* OutQuickslot);

	//CharacterInfo Data
private:
	bool IsSaved = false;

	float SavedPlayerHP = -1.0f;
	float SavedPlayerMP = -1.0f;

	UPROPERTY()
	TArray<FItemSaveData> ArrayInventorySaveData;

	UPROPERTY()
	TArray<FItemSaveData> ArrayQuickSlotSaveData;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = StatTable, Meta = (AllowPrivateAccess = "true"))
	TMap<FName, FJHCharacterStat> CharacterStatMap;

};
