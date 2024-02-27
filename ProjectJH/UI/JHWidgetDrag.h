// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "JHWidgetDrag.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJH_API UJHWidgetDrag : public UDragDropOperation
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UUserWidget> WidgetRef;

	UPROPERTY()
	FVector2D				DragOffset;
};
