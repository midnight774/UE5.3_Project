// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Item/JHItemDataAsset.h"
#include "JHPlayerInventoryInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UJHPlayerInventoryInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTJH_API IJHPlayerInventoryInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetupInventoryWidget(class UJHInventoryWidget* InInventoryWidget) = 0;
	virtual void AddItem(const FPrimaryAssetId& ItemId) = 0;
	virtual void AddItem(class UJHItemDataAsset* InItemData)  = 0;
	virtual void AddItem(class UJHItemDataAsset* InItemData, int32 Idx, int32 Cnt) = 0;
	virtual void UseItem(class UJHItemDataAsset* InItemData)  = 0;
	virtual void RemoveItemFromInventory(class UJHItemDataAsset* InItemData) = 0;
	virtual void AddOverlappingItem(class AJHFieldItemActor* InItemActor) = 0;
	virtual void RemoveOverlappingItem(class AJHFieldItemActor* InItemActor) = 0;
};
