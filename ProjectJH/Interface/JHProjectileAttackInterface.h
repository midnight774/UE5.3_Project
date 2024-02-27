// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "JHProjectileAttackInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UJHProjectileAttackInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTJH_API IJHProjectileAttackInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual class AJHActorProjectile* SpawnProjectile(const FVector& MoveDir, const FVector& SpawnPos, float MoveSpeed = 100.0f, float MoveTime = 2.0f) = 0;
	virtual void StartFireMontage() = 0;
	virtual void AdjustFirePos() = 0;
	virtual void FireProjectile() = 0;
};
