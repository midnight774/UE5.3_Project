// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JHDissolveComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTJH_API UJHDissolveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UJHDissolveComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE void SetDissolveSpeed(float InSpeed) { DissolveSpeed = InSpeed; }
	FORCEINLINE class UMaterialInstanceDynamic* GetDissolveMaterial(const int32 Idx) { return ArrDissolveMaterialInst[Idx]; }
	FORCEINLINE void StartDissolve() { bDissolveEnable = true; }
	FORCEINLINE void SetTargetSkeletal(class USkeletalMeshComponent* InMesh) { TargetSkeletal = InMesh; }
	void SetDissolveReverse(bool IsRev);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DissolveInfo, Meta = (AllowPrivateAccess = "true"))
	float Dissolve;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DissolveInfo, Meta = (AllowPrivateAccess = "true"))
	float DissolveMax;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DissolveInfo, Meta = (AllowPrivateAccess = "true"))
	float DissolveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DissolveInfo, Meta = (AllowPrivateAccess = "true"))
	uint8 bDissolveRev : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DissolveInfo, Meta = (AllowPrivateAccess = "true"))
	uint8 bDissolveEnable : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DissolveInfo, Meta = (AllowPrivateAccess = "true"))
	uint8 bDissolveEnded : 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = DissolveInfo, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UMaterialInstance> DissolveMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = DissolveInfo, Meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<class UMaterialInstanceDynamic>> ArrDissolveMaterialInst;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = DissolveInfo, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USkeletalMeshComponent> TargetSkeletal;

};
