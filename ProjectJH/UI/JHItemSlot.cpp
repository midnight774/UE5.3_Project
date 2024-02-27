// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/JHItemSlot.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Item/JHItemDataAsset.h"
#include "Item/JHItemDataWrapper.h"
#include "Input/Reply.h"
#include "UI/JHDragWidget.h"
#include "UI/JHWidgetDrag.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/TileView.h"
#include "Styling/SlateStyle.h"
#include "UI/JHInventoryWidget.h"
#include "Interface/JHPlayerInventoryInterface.h"
#include "Interface/JHHUDWidgetInterface.h"

UJHItemSlot::UJHItemSlot(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UJHDragWidget> DragWidgetClassRef(TEXT("/Game/ProectJH/UI/JHDragWidget.JHDragWidget_C"));

	if (DragWidgetClassRef.Class)
	{
		DragWidgetClass = DragWidgetClassRef.Class;
	}
}

void UJHItemSlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BackGroundBorder = Cast<UBorder>(GetWidgetFromName(TEXT("BackGround")));
	ItemImage = Cast<UImage>(GetWidgetFromName(TEXT("ItemIconImage")));
	ItemCntText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemCountText")));
}

void UJHItemSlot::NativeConstruct()
{
	Super::NativeConstruct();
}

void UJHItemSlot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UJHItemSlot::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	UJHItemDataWrapper* InItemData = Cast<UJHItemDataWrapper>(ListItemObject);
	SetItemInfo(InItemData);
}

void UJHItemSlot::SetItemInfo(UJHItemDataAsset* InDataAsset, int32 ItemCount)
{
	if (!InDataAsset)
	{
		ItemImage->ReinitializeProperties();
		ItemImage->SetColorAndOpacity(FColor::Black);
		ItemWrapper->SetItemCount(0);
		return;
	}

	if (InDataAsset->GetItemType() == EItemType::End)
	{
		ItemImage->ReinitializeProperties();
		ItemWrapper->SetItemData(InDataAsset);
		ItemImage->SetColorAndOpacity(FColor::Black);
	}

	else
	{
		ItemImage->ReinitializeProperties();
		ItemImage->SetColorAndOpacity(FColor::White);;
		ItemImage->SetBrushFromTexture(InDataAsset->GetIconTexture());
		ItemWrapper->SetItemData(InDataAsset);
		ItemWrapper->SetItemCount(ItemCount);
	}

	SetItemCountText();

	return;


}

void UJHItemSlot::SetItemInfo(UJHItemDataWrapper* InData)
{
	if (!InData)
	{
		ItemImage->ReinitializeProperties();
		ItemImage->SetColorAndOpacity(FColor::White);
		SetItemCountText();
		return;
	}

	UJHItemDataAsset* ItemInfo = InData->GetItemData();
	ItemWrapper = InData;
	SlotIdx = ItemWrapper->GetSlotIdx();

	if (!ItemInfo)
	{
		ItemImage->ReinitializeProperties();
		ItemImage->SetColorAndOpacity(FColor::White);
		SetItemCountText();
		return;
	}

	if (ItemInfo->GetItemType() == EItemType::End)
	{
		ItemImage->ReinitializeProperties();
		ItemImage->SetColorAndOpacity(FColor::White);
		SetItemCountText();

		return;
	}

	ItemImage->ReinitializeProperties();
	ItemImage->SetColorAndOpacity(FColor::White);;
	ItemImage->SetBrushFromTexture(ItemInfo->GetIconTexture());
	SetItemCountText();
}

bool UJHItemSlot::PlusItemCount()
{
	if (ItemWrapper->GetItemCount() < 0)
	{
		return false;
	}

	ItemWrapper->PlusItemCount();

	SetItemCountText();

	return true;
}

bool UJHItemSlot::UseItem()
{
	if (ItemWrapper->GetItemCount() > 0)
	{
		if (!ItemWrapper->UseItem())
		{
			ItemImage->ReinitializeProperties();
			ItemWrapper->SetItemData(nullptr);
			SetItemCountText();
			return false;
		}
	}

	else
	{
		ItemImage->ReinitializeProperties();
		SetItemInfo(nullptr);
		SetItemCountText();
		return false;
	}

	SetItemCountText();

	return true;
}

void UJHItemSlot::SetItemCountText()
{
	if (ItemCntText)
	{
		if (ItemWrapper == nullptr)
		{
			ItemCntText->SetColorAndOpacity(FColor::Transparent);
			return;
		}

		int32 ItemCount = ItemWrapper->GetItemCount();

		if (ItemCount <= 0)
		{
			ItemCntText->SetColorAndOpacity(FColor::Transparent);
		}

		else
		{
			ItemCntText->SetColorAndOpacity(FColor::Black);
		}

		ItemCntText->SetText(FText::FromString(FString::FromInt(ItemCount)));
	}

}

void UJHItemSlot::RefreshIconImage()
{
	if (ItemWrapper)
	{
		UTexture2D* IconTex = ItemWrapper->GetItemData()->GetIconTexture();
		
		if (IconTex)
		{
			ItemImage->ReinitializeProperties();
			ItemImage->SetColorAndOpacity(FColor::White);;
			ItemImage->SetBrushFromTexture(IconTex);
			SetItemCountText();
		}
	}
}

void UJHItemSlot::RequestUseItem()
{
	if (ItemWrapper->GetSlotType() == EItemSlotType::QuickSlot)
	{
		IJHHUDWidgetInterface* HUDInterface = Cast<IJHHUDWidgetInterface>(GetOwningPlayerPawn());

		if (HUDInterface)
		{
			HUDInterface->UseQuickSlotItem(ItemWrapper->GetItemData(), SlotIdx);
		}

		return;
	}

	IJHPlayerInventoryInterface* InventoryInterface = Cast<IJHPlayerInventoryInterface>(GetOwningPlayerPawn());

	if (InventoryInterface)
	{
		InventoryInterface->UseItem(ItemWrapper->GetItemData());
	}
}

int32 UJHItemSlot::GetItemCount()
{
	return ItemWrapper->GetItemCount();
}

UJHItemDataAsset* UJHItemSlot::GetItemInfo()
{
	return ItemWrapper->GetItemData();
}

FReply UJHItemSlot::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Result = Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);

	if (ItemWrapper->GetItemData()->GetItemType() == EItemType::End)
	{
		return Result.Handled();
	}

	IJHPlayerInventoryInterface* InventoryInterface = Cast<IJHPlayerInventoryInterface>(GetOwningPlayerPawn());

	if (InventoryInterface)
	{
		InventoryInterface->UseItem(ItemWrapper->GetItemData());
	}

	return Result.Handled();
}

FReply UJHItemSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Result = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	
	if (ItemWrapper->GetItemData() == nullptr)
	{
		return Result.Handled();
	}

	if (ItemWrapper->GetItemData()->GetItemType() == EItemType::End)
	{
		return Result.Handled();
	}

	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		RequestUseItem();

		return Result.Handled();
	}

	DragOffset = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
	FEventReply ReplyResult = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);

	return ReplyResult.NativeReply;
}

void UJHItemSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if (ItemWrapper->GetItemData()->GetItemType() == EItemType::End)
	{
		return;
	}

	DraggedWidget = CreateWidget<UJHDragWidget>(this, DragWidgetClass);
	DraggedWidget->SetWidgetRef(this);
	DraggedWidget->SetWidgetTexture(ItemWrapper->GetItemData()->GetIconTexture());
	
	UJHWidgetDrag* DragObj = Cast<UJHWidgetDrag>(UWidgetBlueprintLibrary::CreateDragDropOperation(UJHWidgetDrag::StaticClass()));
	DragObj->DefaultDragVisual = DraggedWidget;
	DragObj->WidgetRef = this;
	DragObj->DragOffset = DragOffset;

	OutOperation = DragObj;
}

bool UJHItemSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool Result = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	UJHWidgetDrag* DragOper = Cast<UJHWidgetDrag>(InOperation);

	if (DragOper == nullptr)
	{
		return false;
	}

	UUserWidget* DragWidgetRef = DragOper->WidgetRef;
	
	if (DragWidgetRef == this)
	{
		return Result;
	}

	UJHItemSlot* SlotWidgetRef = Cast<UJHItemSlot>(DragWidgetRef);

	if (SlotWidgetRef)
	{
		UJHItemDataAsset*	RefItemData = SlotWidgetRef->GetItemInfo();
		int32				RefItemCount = SlotWidgetRef->GetItemCount();
		UJHItemDataAsset*	ItemData = GetItemInfo();
		int32				ItemCount = GetItemCount();

		UJHItemDataWrapper* ItemWrapperRef = SlotWidgetRef->GetItemWrapper();

		if (ItemWrapperRef->GetSlotType() != ItemWrapper->GetSlotType())
		{
			APawn* Pawn = GetOwningPlayerPawn();

			if (ItemWrapperRef->GetSlotType() == EItemSlotType::InventorySlot)
			{
				IJHPlayerInventoryInterface* InventoryInterface = Cast<IJHPlayerInventoryInterface>(Pawn);
				IJHHUDWidgetInterface* HUDInterface = Cast<IJHHUDWidgetInterface>(Pawn);

				if (InventoryInterface)
				{
					InventoryInterface->RemoveItemFromInventory(ItemWrapperRef->GetItemData());
					InventoryInterface->AddItem(ItemWrapper->GetItemData(), ItemWrapperRef->GetSlotIdx(), ItemWrapper->GetItemCount());
				}

				if (HUDInterface)
				{
					HUDInterface->AddItemToQuickSlot(ItemWrapperRef->GetItemData(), SlotIdx);
				}
			}

			else
			{
				IJHPlayerInventoryInterface* InventoryInterface = Cast<IJHPlayerInventoryInterface>(Pawn);
				IJHHUDWidgetInterface* HUDInterface = Cast<IJHHUDWidgetInterface>(Pawn);

				if (HUDInterface)
				{
					HUDInterface->RemoveItemFromQuickSlot(ItemWrapperRef->GetItemData());
					HUDInterface->AddItemToQuickSlot(ItemWrapper->GetItemData(), ItemWrapperRef->GetSlotIdx());
				}

				if (InventoryInterface)
				{
					InventoryInterface->AddItem(ItemWrapperRef->GetItemData(), ItemWrapper->GetSlotIdx(), ItemWrapperRef->GetItemCount());
				}
			}

			ItemWrapperRef->InitializeItemData();
			ItemWrapper->InitializeItemData();

			SlotWidgetRef->SetItemInfo(ItemData, ItemCount);
			SetItemInfo(RefItemData, RefItemCount);
			
			return Result;
		}

		else
		{
			APawn* Pawn = GetOwningPlayerPawn();

			if (ItemWrapperRef->GetSlotType() == EItemSlotType::QuickSlot)
			{
				IJHHUDWidgetInterface* HUDInterface = Cast<IJHHUDWidgetInterface>(Pawn);

				HUDInterface->SwapQuickSlotItem(SlotIdx, ItemWrapperRef->GetSlotIdx());
			}

		}

		int32 RefItemCnt = ItemWrapperRef->GetItemCount();

		SlotWidgetRef->SetItemInfo(GetItemInfo(), ItemWrapper->GetItemCount());
		SetItemInfo(RefItemData, RefItemCnt);
	}

	return Result;
}

void UJHItemSlot::SwapSlotInfo(UJHItemDataWrapper* Src, UJHItemDataWrapper* Dest)
{
}
