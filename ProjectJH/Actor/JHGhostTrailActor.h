// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JHGhostTrailActor.generated.h"

UCLASS()
class PROJECTJH_API AJHGhostTrailActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJHGhostTrailActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE void SetGhostColor(const FColor& InColor) { GhostColor = InColor; }
	FORCEINLINE void SetCharacterRef(ACharacter* InCharacterRef) { CharacterRef = InCharacterRef; }
	void SetActiveGhost();
	
	void SetMeshRelativeLocation(const FVector& InLocation);
	void SetMeshRelativeRotation(const FRotator& InRotation);
	void SetMeshRelativeScale(const FVector& InScale);

public:
	void SetupPoseableMeshInfo();
	void UpdateEffectOpacity(float DeltaTime);
	
protected:
	/** Ghost trail material  */
	UPROPERTY(EditDefaultsOnly, Category = "Material")
	TObjectPtr<class UMaterialInterface> GhostTrailMaterial;

	UPROPERTY()
	TObjectPtr<class UMaterialInstanceDynamic> DynamicMtrlInstance;

	/** Ghost trail fade opacity parameter name  */
	UPROPERTY(EditDefaultsOnly, Category = "Opacity")
	FName ScalarParameterName = FName(TEXT("Opacity"));

	/** Ghost trail mesh opacity curve  */
	UPROPERTY(EditDefaultsOnly, Category = "Opacity")
	UCurveFloat* OpacityCurve;

	ACharacter* CharacterRef;

	UPROPERTY(EditDefaultsOnly, Category = "Color")
	FColor GhostColor;

	UPROPERTY(EditDefaultsOnly, Category = "Color")
	float Opacity;

	bool IsActive = false;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	class UPoseableMeshComponent* PoseableMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default")
	USceneComponent* SceneRootComp;
};
