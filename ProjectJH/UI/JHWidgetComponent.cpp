// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/JHWidgetComponent.h"
#include "UI/JHUserWidget.h"

void UJHWidgetComponent::InitWidget()
{
	Super::InitWidget();

	UJHUserWidget* UserWidget = Cast<UJHUserWidget>(GetWidget());

	if (UserWidget)
	{
		UserWidget->SetOwningActor(GetOwner());
	}
}
