// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JHInventoryComponent.generated.h"

DECLARE_DELEGATE_RetVal_OneParam(bool, FOnAddedItemDelegate, class UJHItemDataAsset* /*ItemData*/);
DECLARE_DELEGATE_RetVal_ThreeParams(bool, FOnAddedItemCountDelegate, class UJHItemDataAsset* /*ItemData*/, int32 /*Index*/, int32 /*AddCount*/);
DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnUsedItemDelegate, class UJHItemDataAsset* /*ItemData*/, int32& /*OutItemCount*/);
DECLARE_DELEGATE_OneParam(FOnRemovedItemDelegate, class UJHItemDataAsset* /*ItemData*/);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTJH_API UJHInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UJHInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	FOnAddedItemDelegate		OnAddedItem;
	FOnAddedItemCountDelegate	OnAddedItems;
	FOnUsedItemDelegate			OnUsedItem;
	FOnRemovedItemDelegate		OnRemovedItem;

public:
	bool AddItem(class UJHItemDataAsset* Item);
	bool AddItem(class UJHItemDataAsset* Item, int32 Idx, int32 Count);
	bool UseItem(class UJHItemDataAsset* Item);
	void RemoveFromInventory(class UJHItemDataAsset* Item);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FName, TObjectPtr<class UJHItemDataAsset>> MapItemData;

	const int32 ItemCountMax = 15;
};