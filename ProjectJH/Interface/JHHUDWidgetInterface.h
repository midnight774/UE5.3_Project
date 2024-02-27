// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "JHHUDWidgetInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UJHHUDWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTJH_API IJHHUDWidgetInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetupHUDWidget(class UJHHUDWidget* InHUDWidget) = 0;
	virtual void AddItemToQuickSlot(class UJHItemDataAsset* InItemData, int32 SlotIdx) = 0;
	virtual void UseQuickSlotItem(class UJHItemDataAsset* InItemData, int32 SlotIdx) = 0;
	virtual void RemoveItemFromQuickSlot(class UJHItemDataAsset* InItemData) = 0;
	virtual void SwapQuickSlotItem(const int32 Src, const int32 Dest) = 0;
};
