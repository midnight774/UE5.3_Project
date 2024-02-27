// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "JHItemSlot.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJH_API UJHItemSlot : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	UJHItemSlot(const FObjectInitializer& ObjectInitializer);
	
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject);

public:
	void SetItemInfo(class UJHItemDataAsset* InDataAsset, int32 ItemCount);
	void SetItemInfo(class UJHItemDataWrapper* InData);
	bool PlusItemCount();
	bool UseItem();
	void SetItemCountText();
	void RefreshIconImage();
	void RequestUseItem();
	int32 GetItemCount();

	FORCEINLINE class UJHItemDataWrapper* GetItemWrapper() { return ItemWrapper; }
	FORCEINLINE void SetSlotIdx(const int32 InIdx) { SlotIdx = InIdx; }
	FORCEINLINE const int32 GetSlotIdx() { return SlotIdx; }

	class UJHItemDataAsset* GetItemInfo();

	//Mouse Section;
public:
	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual void SwapSlotInfo(UJHItemDataWrapper* Src, UJHItemDataWrapper* Dest);
	FVector2D DragOffset;
	

	UPROPERTY()
	TSubclassOf<class UJHDragWidget> DragWidgetClass;

	UPROPERTY()
	TObjectPtr<class UJHDragWidget> DraggedWidget;

protected:
	UPROPERTY()
	TObjectPtr<class UBorder> BackGroundBorder;

	UPROPERTY()
	TObjectPtr<class UImage> ItemImage;

	UPROPERTY()
	TObjectPtr<class UTextBlock> ItemCntText;

	UPROPERTY()
	TObjectPtr<class UJHItemDataWrapper> ItemWrapper;

	int32 SlotIdx = -1;

	bool IsStarted = false;

};
