// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JHQuickSlotComponent.generated.h"

DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnAddedToQuickSlotDelegate, class UJHItemDataAsset* /*ItemData*/, int32 /*QuickSlotIdx*/);
DECLARE_DELEGATE_RetVal_ThreeParams(bool, FOnAddedItemsQuickSlotDelegate, class UJHItemDataAsset* /*ItemData*/, int32 /*Index*/, int32 /*AddCount*/);
DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnUsedFromQuickSlotDelegate, int32 /*QuickSlotIdx*/, int32& /*OutItemCount*/);
DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnRemovedFromQuickSlotDelegate, class UJHItemDataAsset* /*ItemData*/, int32& /*OutItemCount*/);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTJH_API UJHQuickSlotComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UJHQuickSlotComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:
	FOnAddedToQuickSlotDelegate OnAddedItem;
	FOnAddedItemsQuickSlotDelegate OnAddedItems;
	FOnUsedFromQuickSlotDelegate OnUsedItem;
	FOnRemovedFromQuickSlotDelegate OnRemovedItem;

public:
	bool AddItem(class UJHItemDataAsset* Item);
	bool AddItem(class UJHItemDataAsset* Item, int32 SlotIdx);
	bool AddItem(class UJHItemDataAsset* Item, int32 SlotIdx, int32 ItemCnt);
	bool UseItem(const int32 QuickSlotIdx);
	void RemoveFromQuickSlot(class UJHItemDataAsset* Item);
	void RemoveFromQuickSlot(const int32 InSlotIdx);
	bool IsEnableAddToQuickSlot(class UJHItemDataAsset* Item);
	void SwapItem(const int32 Src, const int32 Dest);
	FORCEINLINE class UJHItemDataAsset* GetSlotItem(const int32 SlotIdx) { return ArrItemData[SlotIdx]; }


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<class UJHItemDataAsset>> ArrItemData;

	const int32 ItemCountMax = 5;
};
