// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "JHWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJH_API UJHWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

protected:
	virtual void InitWidget() override;
	
};
