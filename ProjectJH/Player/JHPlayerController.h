// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "JHPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJH_API AJHPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AJHPlayerController();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	TSubclassOf<class UJHHUDWidget> HUDWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	TObjectPtr<class UJHHUDWidget> HUDWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	TSubclassOf<class UJHInventoryWidget> InventoryWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	TObjectPtr<class UJHInventoryWidget> InventoryWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	TSubclassOf<class UJHBossWidget> BossWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	TObjectPtr<class UJHBossWidget> BossWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	TObjectPtr<class UJHPotionItemData> RedPotion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	TObjectPtr<class UJHPotionItemData> BluePotion;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CameraShake)
	TSubclassOf<class UCameraShakeBase> DefaultShakeClass;

public:
	void StartDefaultCameraShake();

	UFUNCTION(BlueprintCallable)
	void SwitchInventoryVisibility();

public:
	void SetBossInfo(class AJHCharacterEnemy* InBossRef);

public:
	void AddItem(class UJHItemDataAsset* InItem);
};
