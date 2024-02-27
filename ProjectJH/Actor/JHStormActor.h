// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JHStormActor.generated.h"

UCLASS()
class PROJECTJH_API AJHStormActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJHStormActor();

protected:
	virtual void PostInitializeComponents() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ScaleTick(float DeltaTime);

protected:
	FVector TargetScale = FVector(2.0f, 2.0f, 2.0f);
	bool IsMoving = false;

	FVector TargetPos;
	
public:
	void SetBodyParticle(class UParticleSystem* ParticleSystem, bool bActivate = true);
	void SetHitParticle(class UParticleSystem* ParticleSystem);
	void LookDir();
	void DecideRandTargetPos();

	FORCEINLINE void SetTargetPos(const FVector& InPos) { TargetPos = InPos; }

	FORCEINLINE void SetMoveSpeed(float InSpeed) { MoveSpeed = InSpeed; }
	FORCEINLINE void SetMoveTime(float InMoveTime) { MoveTimeMax = InMoveTime; }
	FORCEINLINE void SetMoveDir(const FVector& InDir) { MoveDir = InDir; }

	FORCEINLINE void SetHitDamage(const float InDamage) { AttackDamage = InDamage; }

	void SetParticleScale(const FVector& InScale);
	void SetSphereRadius(float InRadius);
	void SetCollisionProfile(const FString& ProfileName);

	UFUNCTION()
	void HitEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collider, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBoxComponent> BodyBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Effect, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UParticleSystemComponent> BodyParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Effect, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UParticleSystemComponent> HitParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Effect, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USoundWave> HitSound;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MoveInfo, Meta = (AllowPrivateAccess = "true"))
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MoveInfo, Meta = (AllowPrivateAccess = "true"))
	FVector MoveDir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MoveInfo, Meta = (AllowPrivateAccess = "true"))
	float MoveTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MoveInfo, Meta = (AllowPrivateAccess = "true"))
	float MoveTimeMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MoveInfo, Meta = (AllowPrivateAccess = "true"))
	uint8 bIsMoving : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MoveInfo, Meta = (AllowPrivateAccess = "true"))
	FName CollisionProfileName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MoveInfo, Meta = (AllowPrivateAccess = "true"))
	float AttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MoveInfo, Meta = (AllowPrivateAccess = "true"))
	float AttackRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MoveInfo, Meta = (AllowPrivateAccess = "true"))
	float ChangeDirTimeMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MoveInfo, Meta = (AllowPrivateAccess = "true"))
	float ChangeDirTime;

};
