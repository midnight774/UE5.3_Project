// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/JHItemDataWrapper.h"
#include "Item/JHItemDataAsset.h"

UJHItemDataWrapper::UJHItemDataWrapper()
{
	DefaultItemData = CreateDefaultSubobject<UJHItemDataAsset>(*GetName());
	ItemData = DefaultItemData;
}

void UJHItemDataWrapper::SetItemData(UJHItemDataAsset* InItemData)
{
	ItemData = InItemData;

	if (InItemData == nullptr)
	{
		ItemData = DefaultItemData;
		ItemCount = -1;
	}

	else
	{
		if (ItemData->GetItemType() == EItemType::End)
		{
			ItemCount = -1;
		}

		else
		{
			ItemCount = 1;
		}
	}

}

void UJHItemDataWrapper::PlusItemCount()
{
	++ItemCount;
}

bool UJHItemDataWrapper::UseItem()
{
	if (ItemCount < 0)
	{
		return false;
	}

	--ItemCount;

	if (ItemCount > 0)
	{
		return true;
	}

	return false;

}

void UJHItemDataWrapper::BeginDestroy()
{
	Super::BeginDestroy();

}

void UJHItemDataWrapper::InitializeItemData()
{
	ItemData = DefaultItemData;
	ItemCount = 0;
}
