// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/JHAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/JHCharacterBase.h"

UJHAnimInstance::UJHAnimInstance()
{
	IdleThreshould = 0.3f;
	JumpingThreshould = 100.0f;
}

void UJHAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ACharacter>(GetOwningActor());

	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();
	}
}

void UJHAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Movement)
	{
		Velocity = Movement->Velocity;
		GroundSpeed = Velocity.Size2D();

		bIsIdle = GroundSpeed < IdleThreshould;
		bIsFalling = Movement->IsFalling();
		bIsJumping = bIsFalling & (Velocity.Z > JumpingThreshould);
	}
}

void UJHAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	/*AJHCharacterBase* Character = Cast<AJHCharacterBase>(Owner);

	check(Character);

	UAnimMontage* StartMontage = Character->GetLevelStartMontage();
	if (StartMontage)
	{
		StopAllMontages(0.1f);
		Montage_Play(StartMontage);
	}*/
}
