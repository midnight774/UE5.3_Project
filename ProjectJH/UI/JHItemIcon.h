// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "JHItemIcon.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJH_API UJHItemIcon : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	UJHItemIcon(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

public:
	void SetItemInfo(class UJHItemDataAsset* InItemData);
	FORCEINLINE class UJHItemDataAsset* GetItemInfo() { return ItemInfo; }

protected:
	UPROPERTY()
	TObjectPtr<class UImage> ItemImage;

	UPROPERTY()
	TObjectPtr<class UJHItemDataAsset> ItemInfo;

	UPROPERTY()
	int32 ItemCnt;

	UPROPERTY()
	TObjectPtr<class UTextBlock> ItemCntText;
};
