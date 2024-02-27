// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "JHAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJH_API UJHAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UJHAnimInstance();

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeBeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<class ACharacter> Owner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<class UCharacterMovementComponent> Movement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	FVector Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float GroundSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsIdle : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float IdleThreshould;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsFalling : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsJumping : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsAttacking : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float JumpingThreshould;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float HitFrontDir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float HitSideDir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsHitted : 1;

public:
	FORCEINLINE void SetHitFrontDir(float InRadian) { HitFrontDir = InRadian; }
	FORCEINLINE void SetHitSideDir(float InRadian) { HitSideDir = InRadian; }
	FORCEINLINE void SetHitted(bool InHitted) { bIsHitted = InHitted; }

};
