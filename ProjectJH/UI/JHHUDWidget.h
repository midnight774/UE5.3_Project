// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JHHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJH_API UJHHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UJHHUDWidget(const FObjectInitializer& ObjectInitializer);

public:
	void UpdateHPBar(float InCurrentHP);
	void UpdateMPBar(float InCurrentMP);

	FORCEINLINE void SetMaxHP(float InMax) { MaxHP = InMax; }
	FORCEINLINE void SetMaxMP(float InMax) { MaxMP = InMax; }

	void SetSkillInitialize();

public:
	void UpdateQSkillCoolTime(float CurrentTime, uint8 IsCharged);
	void UpdateESkillCoolTime(float CurrentTime, uint8 IsCharged);
	void UpdateRSkillCoolTime(float CurrentTime, uint8 IsCharged);

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void NativeDestruct() override;

	virtual void BeginDestroy() override;

public:
	bool AddItemToQuickSlot(class UJHItemDataAsset* InItemData, int32 SlotIdx);
	bool AddItemsToQuickSlot(class UJHItemDataAsset* InItemData, int32 SlotIdx, int32 ItemCnt);
	bool UseItem(int32 InSlotIdx, int32& OutItemCount);
	bool RequestUseItem(class UJHItemDataAsset* InItemData);
	bool UseQuickSlotItem(int32 InQuickSlotIdx, int32& OutItemCount);
	bool IsEnableAddToQuickSlot(class UJHItemDataAsset* InItemData);
	const int32 QuickSlotMax = 5;

protected:
	UPROPERTY()
	TObjectPtr<class UProgressBar> HPBar;

	float MaxHP;
	
	UPROPERTY()
	TObjectPtr<class UProgressBar> MPBar;

	float MaxMP;

	UPROPERTY()
	TObjectPtr<class UTextBlock> HPText;

	UPROPERTY()
	TObjectPtr<class UTextBlock> MPText;

	UPROPERTY()
	TObjectPtr<class UListView> ItemQuickSlotList;

	UPROPERTY()
	TObjectPtr<class UTextBlock> QSkillText;

	UPROPERTY()
	TObjectPtr<class UImage> QSkillImage;

	bool  IsQSkillEnable;
	float QSkillCoolTime;
	float QSkillCoolTimeMax;

	UPROPERTY()
	TObjectPtr<class UTextBlock> ESkillText;

	UPROPERTY()
	TObjectPtr<class UImage> ESkillImage;

	bool  IsESkillEnable;
	float ESkillCoolTime;
	float ESkillCoolTimeMax;

	UPROPERTY()
	TObjectPtr<class UTextBlock> RSkillText;

	UPROPERTY()
	TObjectPtr<class UImage> RSkillImage;

	bool  IsRSkillEnable;
	float RSkillCoolTime;
	float RSkillCoolTimeMax;
	
};
