// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/JHItemIcon.h"
#include "Components/Image.h"
#include "Item/JHItemDataAsset.h"

UJHItemIcon::UJHItemIcon(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UJHItemIcon::NativeConstruct()
{
	Super::NativeConstruct();
}

void UJHItemIcon::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UJHItemIcon::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
}

void UJHItemIcon::SetItemInfo(UJHItemDataAsset* InItemData)
{
	ItemInfo = InItemData;
}
