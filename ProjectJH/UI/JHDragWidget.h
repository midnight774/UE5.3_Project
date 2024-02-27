// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "JHDragWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJH_API UJHDragWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	FORCEINLINE void SetWidgetRef(class UUserWidget* InWidget) { WidgetRef = InWidget; }
	FORCEINLINE class UUserWidget* GetWidgetRef() { return  WidgetRef; }
	void SetWidgetTexture(class UTexture2D* InTexture);

protected:
	TObjectPtr<class USizeBox> WidgetSizeBox;
	TObjectPtr<class UImage> DragImage;

	TObjectPtr<class UUserWidget> WidgetRef;
	TObjectPtr<class UTexture2D> WidgetTexture;
	
};
