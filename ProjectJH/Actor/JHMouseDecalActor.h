// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DecalActor.h"
#include "JHMouseDecalActor.generated.h"

UCLASS()
class PROJECTJH_API AJHMouseDecalActor : public ADecalActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJHMouseDecalActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
