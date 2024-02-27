// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/JHQuickSlotComponent.h"
#include "Item/JHItemDataAsset.h"

// Sets default values for this component's properties
UJHQuickSlotComponent::UJHQuickSlotComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UJHQuickSlotComponent::BeginPlay()
{
	Super::BeginPlay();

	ArrItemData.SetNum(ItemCountMax);
	// ...
	
}


// Called every frame
void UJHQuickSlotComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//New Item Is able to Added To QuickSlot Only By Swapping From Inventory;
bool UJHQuickSlotComponent::AddItem(UJHItemDataAsset* Item)
{
	if (Item == nullptr)
	{
		return false;
	}

	if (Item->GetItemType() == EItemType::End)
	{
		return false;
	}

	for (int32 i = 0; i < ItemCountMax; ++i)
	{
		if (ArrItemData[i] == nullptr)
		{
			continue;
		}

		if (ArrItemData[i]->GetItemName() == Item->GetItemName())
		{
			OnAddedItem.Execute(Item, i);
			return true;
		}
	}

	return false;
}

bool UJHQuickSlotComponent::AddItem(UJHItemDataAsset* Item, int32 SlotIdx)
{
	if (Item->GetItemType() == EItemType::End)
	{
		return false;
	}

	if (ArrItemData[SlotIdx] == nullptr)
	{
		ArrItemData[SlotIdx] = Item;
		OnAddedItem.Execute(Item, SlotIdx);
		return true;

	}

	if (ArrItemData[SlotIdx]->GetItemName() == Item->GetItemName())
	{
		OnAddedItem.Execute(Item, SlotIdx);
		return true;
	}

	return false;
}

bool UJHQuickSlotComponent::AddItem(UJHItemDataAsset* Item, int32 SlotIdx, int32 ItemCnt)
{
	if (Item->GetItemType() == EItemType::End)
	{
		return false;
	}

	if (ArrItemData[SlotIdx] == nullptr)
	{
		ArrItemData[SlotIdx] = Item;
		OnAddedItems.Execute(Item, SlotIdx, ItemCnt);
		return true;

	}

	if (ArrItemData[SlotIdx]->GetItemName() == Item->GetItemName())
	{
		OnAddedItems.Execute(Item, SlotIdx, ItemCnt);
		return true;
	}

	return false;
}

bool UJHQuickSlotComponent::UseItem(const int32 QuickSlotIdx)
{
	if (ArrItemData[QuickSlotIdx] == nullptr)
	{
		return false;
	}

	int32 ItemCount = -10;
	
	if (OnUsedItem.Execute(QuickSlotIdx, ItemCount))
	{
		if (ItemCount <= 0)
		{
			RemoveFromQuickSlot(QuickSlotIdx);
		}
	}

	return true;
}

void UJHQuickSlotComponent::RemoveFromQuickSlot(UJHItemDataAsset* Item)
{
	for (int32 i = 0; i < ItemCountMax; ++i)
	{
		if (ArrItemData[i] == nullptr)
		{
			continue;
		}

		if (ArrItemData[i]->GetItemName() == Item->GetItemName())
		{
			RemoveFromQuickSlot(i);
			return;
		}
	}
}

void UJHQuickSlotComponent::RemoveFromQuickSlot(const int32 InSlotIdx)
{
	if (ArrItemData.IsValidIndex(InSlotIdx))
	{
		ArrItemData[InSlotIdx] = nullptr;
	}
}

bool UJHQuickSlotComponent::IsEnableAddToQuickSlot(UJHItemDataAsset* Item)
{
	for (int32 i = 0; i < ItemCountMax; ++i)
	{
		if (ArrItemData[i] == nullptr)
		{
			continue;
		}

		if (ArrItemData[i]->GetItemName() == Item->GetItemName())
		{
			return true;
		}
	}

	return false;
}

void UJHQuickSlotComponent::SwapItem(const int32 Src, const int32 Dest)
{
	if (Src == Dest)
	{
		return;
	}

	UJHItemDataAsset* TempData = ArrItemData[Src];
	ArrItemData[Src] = ArrItemData[Dest];
	ArrItemData[Dest] = TempData;;
}

