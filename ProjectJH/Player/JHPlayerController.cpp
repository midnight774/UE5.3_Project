// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/JHPlayerController.h"
#include "UI/JHHUDWidget.h"
#include "UI/JHInventoryWidget.h"
#include "UI/JHBossWidget.h"
#include "Camera/CameraShakeBase.h"
#include "Item/JHPotionItemData.h"
#include "Character/JHCharacterPlayer.h"
#include "Character/JHCharacterEnemy.h"
#include "Components/CanvasPanel.h"
#include "Interface/JHPlayerInventoryInterface.h"

AJHPlayerController::AJHPlayerController()
{
	static ConstructorHelpers::FClassFinder<UJHHUDWidget> HUDWidgetClsssRef(TEXT("/Game/ProectJH/UI/WBP_JHHUDWidget.WBP_JHHUDWidget_C"));

	if (HUDWidgetClsssRef.Class)
	{
		HUDWidgetClass = HUDWidgetClsssRef.Class;
	}

	static ConstructorHelpers::FClassFinder<UJHInventoryWidget> InventoryWidgetClassRef(TEXT("/Game/ProectJH/UI/WBP_JHInventoryWidget.WBP_JHInventoryWidget_C"));

	if (InventoryWidgetClassRef.Class)
	{
		InventoryWidgetClass = InventoryWidgetClassRef.Class;
	}

	static ConstructorHelpers::FClassFinder<UJHBossWidget> BossWidgetClassRef(TEXT("/Game/ProectJH/UI/WBP_BossWidget.WBP_BossWidget_C"));

	if (BossWidgetClassRef.Class)
	{
		BossWidgetClass = BossWidgetClassRef.Class;
	}

	static ConstructorHelpers::FClassFinder<UCameraShakeBase> CamShakeClassRef(TEXT("/Game/ProectJH/Blueprints/DefaultShake.DefaultShake_C"));

	if (CamShakeClassRef.Class)
	{
		DefaultShakeClass = CamShakeClassRef.Class;
	}

	static ConstructorHelpers::FObjectFinder<UJHPotionItemData> RedPotionItemRef(TEXT("/Script/ProjectJH.JHPotionItemData'/Game/ProectJH/ItemData/RedPotionData.RedPotionData'"));

	if (RedPotionItemRef.Object)
	{
		RedPotion = RedPotionItemRef.Object;
	}


	static ConstructorHelpers::FObjectFinder<UJHPotionItemData> BluePotionItemRef(TEXT("/Script/ProjectJH.JHPotionItemData'/Game/ProectJH/ItemData/BluePotionData.BluePotionData'"));

	if (BluePotionItemRef.Object)
	{
		BluePotion = BluePotionItemRef.Object;
	}

	
}

void AJHPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AJHPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (HUDWidgetClass)
	{
		HUDWidget = CreateWidget<UJHHUDWidget>(this, HUDWidgetClass);

		if (HUDWidget)
		{
			HUDWidget->AddToViewport();
		}
	}

	if (InventoryWidgetClass)
	{
		//InventoryWidget = Cast<UJHInventoryWidget>(HUDWidget->GetWidgetFromName(TEXT("WBP_JHInventory_Widget")));
		InventoryWidget = CreateWidget<UJHInventoryWidget>(this, InventoryWidgetClass);

		if (InventoryWidget)
		{
			UCanvasPanel* Panel = Cast<UCanvasPanel>((HUDWidget->GetWidgetFromName(TEXT("HUDPanel"))));
			Panel->AddChildToCanvas(InventoryWidget);
			InventoryWidget->RemoveFromParent();
			InventoryWidget->AddToViewport(0);
			InventoryWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
			InventoryWidget->SetRenderOpacity(0.0f);

			int32 SizeX, SizeY;
			
			GetViewportSize(SizeX, SizeY);
			SizeX *= 2;
		
			InventoryWidget->SetPositionInViewport(FVector2D(SizeX / 3.0 * 2.0, SizeY / 3.0), false);
		}
	}

	if (BossWidgetClass)
	{
		BossWidget = CreateWidget<UJHBossWidget>(this, BossWidgetClass);
		BossWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	SetInputMode(FInputModeGameOnly());
}

void AJHPlayerController::StartDefaultCameraShake()
{
	if (PlayerCameraManager && DefaultShakeClass)
	{
		PlayerCameraManager->StartCameraShake(DefaultShakeClass);
	}
}

void AJHPlayerController::SwitchInventoryVisibility()
{
	if (InventoryWidget == nullptr)
	{
		InventoryWidget = Cast<UJHInventoryWidget>(HUDWidget->GetWidgetFromName(TEXT("InventoryWidget")));
	}

	if (InventoryWidget->GetVisibility() == ESlateVisibility::HitTestInvisible)
	{
		IJHPlayerInventoryInterface* JHPlayer = Cast<IJHPlayerInventoryInterface>(GetPawn());
		SetInputMode(FInputModeUIOnly());
		InventoryWidget->SetVisibility(ESlateVisibility::Visible);
		InventoryWidget->SetRenderOpacity(1.0f);
		bShowMouseCursor = true;
	}

	else
	{
		SetInputMode(FInputModeGameOnly());
		InventoryWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
		InventoryWidget->SetRenderOpacity(0.0f);
		bShowMouseCursor = false;
	}
}

void AJHPlayerController::SetBossInfo(AJHCharacterEnemy* InBossRef)
{
	InBossRef->SetupBossWidget(BossWidget);
	BossWidget->SetVisibility(ESlateVisibility::HitTestInvisible);

	BossWidget->AddToViewport(0);
}

void AJHPlayerController::AddItem(UJHItemDataAsset* InItem)
{
	IJHPlayerInventoryInterface* JHPlayer = Cast<IJHPlayerInventoryInterface>(GetPawn());
	JHPlayer->AddItem(RedPotion);
}

