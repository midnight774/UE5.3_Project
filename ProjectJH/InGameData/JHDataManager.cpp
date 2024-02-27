// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameData/JHDataManager.h"
#include "Item/JHItemDataAsset.h"
#include "Component//JHInventoryComponent.h"
#include "Component//JHQuickSlotComponent.h"

DEFINE_LOG_CATEGORY(LogJHDataManager);

UJHDataManager::UJHDataManager()
{
	ConstructorHelpers::FObjectFinder<UDataTable> CharacterStatRef(TEXT("/Script/Engine.DataTable'/Game/ProectJH/InGameData/CharacterStat.CharacterStat'"));

	if (CharacterStatRef.Object)
	{
		const UDataTable* DataTable = CharacterStatRef.Object;

		TMap<FName, uint8*> TableMap = DataTable->GetRowMap();

		int32 TableRowCnt = TableMap.Num();
		check(TableRowCnt > 0);

		for (const auto& Row : TableMap)
		{
			FJHCharacterStat* Stat = reinterpret_cast<FJHCharacterStat*>(Row.Value);
			CharacterStatMap.Add(Row.Key, *Stat);
		}

	}

	ArrayInventorySaveData.SetNum(15);
	ArrayQuickSlotSaveData.SetNum(5);
}

UJHDataManager* UJHDataManager::GetInst()
{
	UJHDataManager* DataManager = Cast<UJHDataManager>(GEngine->GameSingleton);

	if (DataManager)
	{
		return DataManager;
	}

	UE_LOG(LogJHDataManager, Error, TEXT("Lost Data Manager"));
	return nullptr;
}

const FJHCharacterStat* UJHDataManager::FindCharacterStat(const FName& InName)
{
	FJHCharacterStat* CharacterStat = CharacterStatMap.Find(InName);

	if (CharacterStat)
	{
		return CharacterStat;
	}

	return nullptr;
}

void UJHDataManager::SaveCharacterStat(UJHCharacterStatComponent* StatComponent)
{
}

void UJHDataManager::LoadCharacterStat(UJHCharacterStatComponent* StatComponent)
{
}

void UJHDataManager::SaveInventoryData(UJHItemDataAsset* InItem, int32 Idx, int32 Cnt)
{
	if (InItem->GetItemType() == EItemType::End)
	{
		FItemSaveData Data;
		ArrayInventorySaveData[Idx] = Data;
		return;
	}

	FItemSaveData Data;
	Data.Item = InItem;
	Data.ItemCnt = Cnt;

	ArrayInventorySaveData[Idx] = Data;
}

void UJHDataManager::SaveQuickSlotData(UJHItemDataAsset* InItem, int32 Idx, int32 Cnt)
{
	if (InItem->GetItemType() == EItemType::End)
	{
		FItemSaveData Data;
		ArrayQuickSlotSaveData[Idx] = Data;
		return;
	}

	FItemSaveData Data;
	Data.Item = InItem;
	Data.ItemCnt = Cnt;

	ArrayQuickSlotSaveData[Idx] = Data;
}

void UJHDataManager::LoadInventoryData(UJHInventoryComponent* Inventory)
{
}

void UJHDataManager::LoadQuickSlotData(UJHQuickSlotComponent* Quickslot)
{
}

void UJHDataManager::SaveCharacterItemData(UJHInventoryComponent* Inventory, UJHQuickSlotComponent* Quickslot)
{
}

void UJHDataManager::LoadCharacterItemData(UJHInventoryComponent* OutInventory, UJHQuickSlotComponent* OutQuickslot)
{
	for (int i = 0; i < 15; ++i)
	{
		if (ArrayInventorySaveData[i].Item == nullptr)
			continue;

		OutInventory->AddItem(ArrayInventorySaveData[i].Item, i, ArrayInventorySaveData[i].ItemCnt);
	}

	for (int i = 0; i < 5; ++i)
	{
		if (ArrayQuickSlotSaveData[i].Item == nullptr)
			continue;

		OutQuickslot->AddItem(ArrayQuickSlotSaveData[i].Item, i, ArrayQuickSlotSaveData[i].ItemCnt);
	}
}
