// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JHInventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJH_API UJHInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UJHInventoryWidget(const FObjectInitializer& ObjectInitializer);

public:
	bool AddItemToInventory(class UJHItemDataAsset* InItemData);
	bool AddItemsToInventory(class UJHItemDataAsset* InItemData, int32 ItemIdx, int32 ItemCnt);
	bool UseItem(class UJHItemDataAsset* InItemData, int32& OutItemCount);
	bool RequestUseItem(class UJHItemDataAsset* InItemData);
	void RemoveItemFromInventory(class UJHItemDataAsset* InItemData);

protected:
	virtual void NativeOnInitialized();

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void BeginDestroy() override;
	virtual void NativeDestruct() override;

protected:
	UPROPERTY()
	TObjectPtr<class UTileView> InventoryTileView;

	UPROPERTY()
	TSubclassOf<class UJHItemSlot> InventorySlotClass;

	UPROPERTY()
	TMap<FName, TObjectPtr<class UJHItemDataAsset>> MapItem;

	const int32 InventoryItemMaxCount = 15;
};
