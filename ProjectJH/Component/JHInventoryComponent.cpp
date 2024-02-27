// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/JHInventoryComponent.h"
#include "Item/JHItemDataAsset.h"

// Sets default values for this component's properties
UJHInventoryComponent::UJHInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UJHInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UJHInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UJHInventoryComponent::AddItem(UJHItemDataAsset* Item)
{
	if (Item->GetItemType() == EItemType::End)
	{
		return false;
	}

	auto ItemIter = MapItemData.Find(Item->GetItemName());

	if (ItemIter == nullptr)
	{
		int32 CurrentItemCount = MapItemData.Num();

		if (CurrentItemCount > ItemCountMax)
		{
			return false;
		}

		MapItemData.Add(Item->GetItemName(), Item);
		OnAddedItem.Execute(Item);
	}

	else
	{
		OnAddedItem.Execute(Item);
	}

	return true;
}

bool UJHInventoryComponent::AddItem(UJHItemDataAsset* Item, int32 Idx, int32 Count)
{
	if (Item->GetItemType() == EItemType::End)
	{
		return false;
	}

	MapItemData.Add(Item->GetItemName(), Item);
	OnAddedItems.Execute(Item, Idx, Count);


	return true;
}

bool UJHInventoryComponent::UseItem(UJHItemDataAsset* Item)
{
	FName ItemName = Item->GetItemName();
	auto ItemIter = MapItemData.Find(ItemName);

	if (ItemIter)
	{
		int32 ItemCount = -10;
		
		if (OnUsedItem.Execute(Item, ItemCount))
		{
			if (ItemCount <= 0)
			{
				MapItemData.Remove(ItemName);
				OnRemovedItem.ExecuteIfBound(Item);
			}

			return true;
		}
	}
	
	return false;
}

void UJHInventoryComponent::RemoveFromInventory(UJHItemDataAsset* Item)
{
	FName ItemName = Item->GetItemName();
	auto ItemIter = MapItemData.Find(ItemName);

	if (ItemIter)
	{
		int32 ItemCount = -10;

		if (ItemCount <= 0)
		{
			MapItemData.Remove(ItemName);
			OnRemovedItem.ExecuteIfBound(Item);
		}
	}
}
