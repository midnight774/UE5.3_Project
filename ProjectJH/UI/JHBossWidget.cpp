// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/JHBossWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

UJHBossWidget::UJHBossWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UJHBossWidget::UpdateHPBar(float InCurrentHP)
{
	HPBar->SetPercent(InCurrentHP / MaxHP);
}

void UJHBossWidget::SetBossName(const FName& InName)
{
	BossName = InName;
}

void UJHBossWidget::SetBossDead()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UJHBossWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("BossHPBar")));
	BossNameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("BossName")));

	check(HPBar);
	check(BossNameText);

	BossNameText->SetText(FText::FromName(BossName));
}

void UJHBossWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}
