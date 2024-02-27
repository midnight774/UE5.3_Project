// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/JHDragWidget.h"
#include "Components/SizeBox.h"
#include "Components/Image.h"
#include "Blueprint/WidgetTree.h"

void UJHDragWidget::NativeOnInitialized()
{
	WidgetSizeBox = Cast<USizeBox>(GetWidgetFromName(TEXT("WidgetSizeBox")));
	DragImage = Cast<UImage>(GetWidgetFromName(TEXT("WidgetRefImage")));
}

void UJHDragWidget::NativeConstruct()
{
	if (WidgetRef)
	{
		FVector2D WidgetSize = WidgetRef->GetDesiredSize();

		if (WidgetSizeBox)
		{
			WidgetSizeBox->SetWidthOverride(WidgetSize.X);
			WidgetSizeBox->SetHeightOverride(WidgetSize.Y);
		}

		if (WidgetTexture)
		{
			DragImage->SetBrushFromTexture(WidgetTexture);
			DragImage->SetOpacity(0.5f);
		}
	}
}

void UJHDragWidget::SetWidgetTexture(UTexture2D* InTexture)
{
	WidgetTexture = InTexture;
}
