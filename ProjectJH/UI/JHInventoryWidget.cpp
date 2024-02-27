// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/JHInventoryWidget.h"
#include "Components/TileView.h"
#include "Item/JHItemDataAsset.h"
#include "Item/JHItemDataWrapper.h"
#include "UI/JHItemSlot.h"
#include "Interface/JHPlayerInventoryInterface.h"
#include "InGameData/JHDataManager.h"

UJHInventoryWidget::UJHInventoryWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UJHItemSlot> ItemSlotClassRef(TEXT("/Game/ProectJH/UI/WBP_JHItemSlot.WBP_JHItemSlot_C"));

	if (ItemSlotClassRef.Class)
	{
		InventorySlotClass = ItemSlotClassRef.Class;
	}
}

bool UJHInventoryWidget::AddItemToInventory(UJHItemDataAsset* InItemData)
{
	if (!InItemData)
	{
		return false;
	}

	if (InItemData->GetItemType() == EItemType::End)
	{
		return false;
	}

	const FName ItemName = InItemData->GetItemName();
	auto ItemIter = MapItem.Find(ItemName);

	if (ItemIter == nullptr)
	{
		int32 ItemCnt = MapItem.Num();

		if (MapItem.Num() >= InventoryItemMaxCount)
		{
			return false;
		}

		for (int i = 0; i < InventoryItemMaxCount; ++i)
		{
			UJHItemDataWrapper* SlotItemWrapper = Cast<UJHItemDataWrapper>(InventoryTileView->GetItemAt(i));

			if (SlotItemWrapper->GetItemData()->GetItemType() == EItemType::End)
			{
				SlotItemWrapper->SetItemData(InItemData);
				InventoryTileView->RequestRefresh();
				MapItem.Add(ItemName, InItemData);

				UUserWidget* ItemObj = InventoryTileView->GetEntryWidgetFromItem(SlotItemWrapper);
				UJHItemSlot* ItemSlot = Cast<UJHItemSlot>(ItemObj);

				if (ItemSlot)
				{
					ItemSlot->RefreshIconImage();
				}

				break;
			}

		}
	}

	else
	{
		for (int i = 0; i < InventoryItemMaxCount; ++i)
		{
			UJHItemDataWrapper* SlotItemData = Cast<UJHItemDataWrapper>(InventoryTileView->GetItemAt(i));

			if (SlotItemData->GetItemData()->GetItemName() == InItemData->GetItemName())
			{
				UUserWidget* ItemObj = InventoryTileView->GetEntryWidgetFromItem(SlotItemData);
				UJHItemSlot* ItemSlot = Cast<UJHItemSlot>(ItemObj);

				if (!ItemSlot->PlusItemCount())
				{
					return false;
				}

				InventoryTileView->RequestRefresh();
				break;
			}
		}

	}

	return true;

}

bool UJHInventoryWidget::AddItemsToInventory(UJHItemDataAsset* InItemData, int32 ItemIdx, int32 ItemCnt)
{
	UJHItemDataWrapper* SlotItemWrapper = Cast<UJHItemDataWrapper>(InventoryTileView->GetItemAt(ItemIdx));

	if (SlotItemWrapper->GetItemData()->GetItemType() == EItemType::End)
	{
		SlotItemWrapper->SetItemData(InItemData);
		SlotItemWrapper->SetItemCount(ItemCnt);
		InventoryTileView->RequestRefresh();

		UUserWidget* ItemObj = InventoryTileView->GetEntryWidgetFromItem(SlotItemWrapper);
		UJHItemSlot* ItemSlot = Cast<UJHItemSlot>(ItemObj);
		MapItem.Add(InItemData->GetItemName(), InItemData);

		if (ItemSlot)
		{
			ItemSlot->RefreshIconImage();
		}

		return true;
	}
	
	return false;
}

bool UJHInventoryWidget::UseItem(UJHItemDataAsset* InItemData, int32& OutItemCount)
{
	if (!InItemData)
	{
		return false;
	}

	if (InItemData->GetItemType() == EItemType::End)
	{
		return false;
	}

	const FName ItemName = InItemData->GetItemName();
	auto ItemIter = MapItem.Find(ItemName);

	if (ItemIter == nullptr)
	{
		return false;
	}

	else
	{
		for (int i = 0; i < InventoryItemMaxCount; ++i)
		{
			UJHItemDataWrapper* SlotItemData = Cast<UJHItemDataWrapper>(InventoryTileView->GetItemAt(i));

			if (SlotItemData->GetItemData()->GetItemName() == InItemData->GetItemName())
			{
				UUserWidget* ItemObj = InventoryTileView->GetEntryWidgetFromItem(SlotItemData);
				UJHItemSlot* ItemSlot = Cast<UJHItemSlot>(ItemObj);

				if (!ItemSlot->UseItem())
				{
					MapItem.Remove(ItemName);
				}

				OutItemCount = ItemSlot->GetItemCount();
				break;
			}
		}
	}

	InventoryTileView->RequestRefresh();
	return true;
}

bool UJHInventoryWidget::RequestUseItem(UJHItemDataAsset* InItemData)
{
	if (!InItemData)
	{
		return false;
	}

	if (InItemData->GetItemType() == EItemType::End)
	{
		return false;
	}

	const FName ItemName = InItemData->GetItemName();
	auto ItemIter = MapItem.Find(ItemName);

	if (ItemIter == nullptr)
	{
		return false;
	}

	else
	{
		IJHPlayerInventoryInterface* InventoryInterface = Cast<IJHPlayerInventoryInterface>(GetOwningPlayerPawn());
		
		if (InventoryInterface)
		{
			InventoryInterface->UseItem(InItemData);
			InventoryTileView->RequestRefresh();
			return true;
		}

		return false;
	}
}

void UJHInventoryWidget::RemoveItemFromInventory(UJHItemDataAsset* InItemData)
{
	const FName ItemName = InItemData->GetItemName();
	
	MapItem.Remove(ItemName);

}

void UJHInventoryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InventoryTileView = Cast<UTileView>(GetWidgetFromName(TEXT("InventoryTile")));

	if (InventoryTileView)
	{
		int32 Num = InventoryItemMaxCount - InventoryTileView->GetNumItems();

		for (int32 i = 0; i < Num; ++i)
		{
			UJHItemDataWrapper* NewItem = NewObject<UJHItemDataWrapper>(this);
			NewItem->SetSlotType(EItemSlotType::InventorySlot);
			NewItem->SetSlotIdx(i);
			InventoryTileView->AddItem(NewItem);
		}
	} 
}

void UJHInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();	

	IJHPlayerInventoryInterface* InventoryInterface = Cast<IJHPlayerInventoryInterface>(GetOwningPlayerPawn());

	if (InventoryInterface)
	{
		InventoryInterface->SetupInventoryWidget(this);
	}

	//Initialize();
}

void UJHInventoryWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UJHInventoryWidget::BeginDestroy()
{
	Super::BeginDestroy();
}

void UJHInventoryWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (InventoryTileView == nullptr)
		return;

	if (InventoryTileView->GetNumItems() == 0)
	{
		return;
	}
	UJHDataManager* DataManager = UJHDataManager::GetInst();

	for (int i = 0; i < InventoryItemMaxCount; ++i)
	{
		UJHItemDataWrapper* SlotItemData = Cast<UJHItemDataWrapper>(InventoryTileView->GetItemAt(i));

		UUserWidget* ItemObj = InventoryTileView->GetEntryWidgetFromItem(SlotItemData);
		if (ItemObj == nullptr)
			return;
		UJHItemSlot* ItemSlot = Cast<UJHItemSlot>(ItemObj);

		DataManager->SaveInventoryData(ItemSlot->GetItemInfo(), i, ItemSlot->GetItemCount());
	}
}
