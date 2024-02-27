// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/JHHUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/ListView.h"
#include "UI/JHItemSlot.h"
#include "Item/JHItemDataWrapper.h"
#include "Item/JHItemDataAsset.h"
#include "Interface/JHPlayerInventoryInterface.h"
#include "Interface/JHHUDWidgetInterface.h"
#include "InGameData/JHDataManager.h"

UJHHUDWidget::UJHHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UJHHUDWidget::UpdateHPBar(float InCurrentHP)
{
	HPBar->SetPercent(InCurrentHP / MaxHP);
	FString HPString = FString::Printf(TEXT("%.0f / %.0f"), InCurrentHP, MaxHP);
	HPText->SetText(FText::FromString(HPString));
}

void UJHHUDWidget::UpdateMPBar(float InCurrentMP)
{
	MPBar->SetPercent(InCurrentMP / MaxMP);
	FString MPString = FString::Printf(TEXT("%.0f / %.0f"), InCurrentMP, MaxMP);
	MPText->SetText(FText::FromString(MPString));
}

void UJHHUDWidget::SetSkillInitialize()
{
}

void UJHHUDWidget::UpdateQSkillCoolTime(float CurrentTime, uint8 IsCharged)
{
	FString StrTime = FString::Printf(TEXT("%.1f"), CurrentTime);

	FText TimeText = FText::FromString(StrTime);
	QSkillText->SetText(TimeText);

	if (IsCharged)
	{
		QSkillImage->SetColorAndOpacity(FColor(255, 255, 255, 255));
		QSkillText->SetOpacity(0);
	}

	else
	{
		QSkillImage->SetColorAndOpacity(FColor(122, 122, 122, 255));
		QSkillText->SetOpacity(1);
	}
}

void UJHHUDWidget::UpdateESkillCoolTime(float CurrentTime, uint8 IsCharged)
{
	FString StrTime = FString::Printf(TEXT("%.1f"), CurrentTime);

	FText TimeText = FText::FromString(StrTime);
	ESkillText->SetText(TimeText);

	if (IsCharged)
	{
		ESkillImage->SetColorAndOpacity(FColor(255, 255, 255, 255));
		ESkillText->SetOpacity(0);
	}

	else
	{
		ESkillImage->SetColorAndOpacity(FColor(122, 122, 122, 255));
		ESkillText->SetOpacity(1);
	}
}

void UJHHUDWidget::UpdateRSkillCoolTime(float CurrentTime, uint8 IsCharged)
{
	FString StrTime = FString::Printf(TEXT("%.1f"), CurrentTime);

	FText TimeText = FText::FromString(StrTime);
	RSkillText->SetText(TimeText);

	if (IsCharged)
	{
		RSkillImage->SetColorAndOpacity(FColor(255, 255, 255, 255));
		RSkillText->SetOpacity(0);
	}

	else
	{
		RSkillImage->SetColorAndOpacity(FColor(122, 122, 122, 255));
		RSkillText->SetOpacity(1);
	}
}

void UJHHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HPBarWidget")));
	MPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MPBarWidget")));

	HPText = Cast<UTextBlock>(GetWidgetFromName(TEXT("HPText")));
	MPText = Cast<UTextBlock>(GetWidgetFromName(TEXT("MPText")));

	QSkillText = Cast<UTextBlock>(GetWidgetFromName(TEXT("QSkillCoolTimeText")));
	ESkillText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ESkillCoolTimeText")));
	RSkillText = Cast<UTextBlock>(GetWidgetFromName(TEXT("RSkillCoolTimeText")));

	QSkillImage = Cast<UImage>(GetWidgetFromName(TEXT("QSkillImage")));
	ESkillImage = Cast<UImage>(GetWidgetFromName(TEXT("ESkillImage")));
	RSkillImage = Cast<UImage>(GetWidgetFromName(TEXT("RSkillImage")));

	ItemQuickSlotList = Cast<UListView>(GetWidgetFromName(TEXT("QuickSlotList")));
	
	for (int i = 0; i < QuickSlotMax; ++i)
	{
		UJHItemDataWrapper* ItemWrapper = NewObject<UJHItemDataWrapper>(this);
		ItemWrapper->SetSlotType(EItemSlotType::QuickSlot);
		ItemWrapper->SetSlotIdx(i);
		ItemQuickSlotList->AddItem(ItemWrapper);
	}

	QSkillText->SetOpacity(0.0f);
	ESkillText->SetOpacity(0.0f);
	RSkillText->SetOpacity(0.0f);

	IsQSkillEnable = true;
	IsESkillEnable = true;
	IsRSkillEnable = true;

	IJHHUDWidgetInterface* HUDInterface = Cast<IJHHUDWidgetInterface>(GetOwningPlayerPawn());

	if (HUDInterface)
	{
		HUDInterface->SetupHUDWidget(this);
	}

	FString HPString = FString::Printf(TEXT("%.0f / %.0f"), MaxHP, MaxHP);
	HPText->SetText(FText::FromString(HPString));
	FString MPString = FString::Printf(TEXT("%.0f / %.0f"), MaxMP, MaxMP);
	MPText->SetText(FText::FromString(MPString));

}

void UJHHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UJHHUDWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (ItemQuickSlotList == nullptr)
		return;

	if (ItemQuickSlotList->GetNumItems() == 0)
	{
		return;
	}

	UJHDataManager* DataManager = UJHDataManager::GetInst();

	for (int i = 0; i < QuickSlotMax; ++i)
	{
		UJHItemDataWrapper* SlotItemData = Cast<UJHItemDataWrapper>(ItemQuickSlotList->GetItemAt(i));


		UUserWidget* ItemObj = ItemQuickSlotList->GetEntryWidgetFromItem(SlotItemData);
		
		if (ItemObj == nullptr)
			return;

		UJHItemSlot* ItemSlot = Cast<UJHItemSlot>(ItemObj);

		DataManager->SaveQuickSlotData(ItemSlot->GetItemInfo(), i, ItemSlot->GetItemCount());
	}
}

void UJHHUDWidget::BeginDestroy()
{
	Super::BeginDestroy();

	
}

bool UJHHUDWidget::AddItemToQuickSlot(UJHItemDataAsset* InItemData, int32 SlotIdx)
{
	if (!InItemData)
	{
		return false;
	}

	if (InItemData->GetItemType() == EItemType::End)
	{
		return false;
	}

	UJHItemDataWrapper* SlotItemData = Cast<UJHItemDataWrapper>(ItemQuickSlotList->GetItemAt(SlotIdx));

	if (SlotItemData)
	{
		if (SlotItemData->GetItemData()->GetItemName() == InItemData->GetItemName())
		{
			UUserWidget* ItemObj = ItemQuickSlotList->GetEntryWidgetFromItem(SlotItemData);
			UJHItemSlot* ItemSlot = Cast<UJHItemSlot>(ItemObj);

			if (!ItemSlot->PlusItemCount())
			{
				return false;
			}

			ItemQuickSlotList->RequestRefresh();
			return true;
		}
	}

	return false;
}

bool UJHHUDWidget::AddItemsToQuickSlot(UJHItemDataAsset* InItemData, int32 SlotIdx, int32 ItemCnt)
{
	if (!InItemData)
	{
		return false;
	}

	if (InItemData->GetItemType() == EItemType::End)
	{
		return false;
	}

	UJHItemDataWrapper* SlotItemData = Cast<UJHItemDataWrapper>(ItemQuickSlotList->GetItemAt(SlotIdx));

	if (SlotItemData)
	{
		SlotItemData->SetItemData(InItemData);
		SlotItemData->SetItemCount(ItemCnt);

		return true;
	}

	return false;
}

bool UJHHUDWidget::UseItem(int32 InSlotIdx, int32& OutItemCount)
{
	return false;
}

bool UJHHUDWidget::RequestUseItem(UJHItemDataAsset* InItemData)
{
	return false;
}

bool UJHHUDWidget::UseQuickSlotItem(int32 InQuickSlotIdx, int32& OutItemCount)
{
	UJHItemDataWrapper* Item = Cast<UJHItemDataWrapper>(ItemQuickSlotList->GetItemAt(InQuickSlotIdx));

	if (Item)
	{
		UUserWidget* ItemObj = ItemQuickSlotList->GetEntryWidgetFromItem(Item);
		UJHItemSlot* ItemSlot = Cast<UJHItemSlot>(ItemObj);

		ItemSlot->UseItem();
		OutItemCount = ItemSlot->GetItemCount();
		ItemQuickSlotList->RequestRefresh();

		return true;
	}

	return false;
}

bool UJHHUDWidget::IsEnableAddToQuickSlot(UJHItemDataAsset* InItemData)
{
	FName InItemName = InItemData->GetItemName();

	for (int i = 0; i < QuickSlotMax; ++i)
	{
		UJHItemDataWrapper* ItemWrapper = Cast<UJHItemDataWrapper>(ItemQuickSlotList->GetItemAt(i));

		if (ItemWrapper)
		{
			if (ItemWrapper->GetItemData()->GetItemName() == InItemName)
			{
				UUserWidget* ItemObj = ItemQuickSlotList->GetEntryWidgetFromItem(ItemWrapper);
				UJHItemSlot* ItemSlot = Cast<UJHItemSlot>(ItemObj);

				if (ItemSlot)
				{
					ItemSlot->PlusItemCount();
					ItemSlot->RefreshIconImage();
				}

				ItemQuickSlotList->RequestRefresh();

				return true;
			}
		}
	}

	return false;
}
