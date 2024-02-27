// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/JHUserWidget.h"
#include "JHBossWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJH_API UJHBossWidget : public UJHUserWidget
{
	GENERATED_BODY()

public:
	UJHBossWidget(const FObjectInitializer& ObjectInitializer);

public:
	void UpdateHPBar(float InCurrentHP);

	FORCEINLINE void SetMaxHP(float InMax) { MaxHP = InMax; }
	void SetBossName(const FName& InName);
	void SetBossDead();

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	UPROPERTY()
	TObjectPtr<class UProgressBar> HPBar;

	float MaxHP;

	UPROPERTY()
	TObjectPtr<class UTextBlock> BossNameText;

	UPROPERTY()
	FName BossName;

};
