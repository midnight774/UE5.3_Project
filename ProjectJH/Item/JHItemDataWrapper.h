// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "JHItemDataWrapper.generated.h"

/**
 * 
 */
UENUM()
enum class EItemSlotType : uint8
{
	InventorySlot,
	QuickSlot
};

UCLASS()
class PROJECTJH_API UJHItemDataWrapper : public UObject
{
	GENERATED_BODY()
	
public:
	UJHItemDataWrapper();

public:
	void SetItemData(class UJHItemDataAsset* InItemData);
	void PlusItemCount();
	bool UseItem();
	FORCEINLINE void SetSlotType(EItemSlotType InSlotType) { SlotType = InSlotType; }
	FORCEINLINE const EItemSlotType GetSlotType() { return SlotType; }
	FORCEINLINE class UJHItemDataAsset* GetItemData() { return ItemData; }
	FORCEINLINE int32 GetItemCount() { return ItemCount; }
	FORCEINLINE void SetItemCount(int32 InCount) { ItemCount = InCount; }
	FORCEINLINE void SetSlotIdx(const int32 InIdx) { SlotIdx = InIdx; }
	FORCEINLINE const int32 GetSlotIdx() { return SlotIdx; }

	virtual void BeginDestroy() override;
	void InitializeItemData();

protected:
	UPROPERTY()
	TObjectPtr<class UJHItemDataAsset> ItemData;

	UPROPERTY()
	TObjectPtr<class UJHItemDataAsset> DefaultItemData;

	UPROPERTY()
	int32 ItemCount = -1;

	UPROPERTY()
	EItemSlotType SlotType;

	UPROPERTY()
	int32 SlotIdx = -1;

};
