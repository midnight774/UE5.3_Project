// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/JHWorldWidgetInterface.h"
#include "JHFieldItemActor.generated.h"

UCLASS()
class PROJECTJH_API AJHFieldItemActor : public AActor, public IJHWorldWidgetInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJHFieldItemActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetItemData(class UJHItemDataAsset* InItemData);

protected:
	void SetupItemActor();

public:
	void SetSelected(bool bSelected);
	void SetGroundLocation();

protected:
	UPROPERTY()
	TObjectPtr<class USceneComponent> RootSceneComponent;

	UPROPERTY()
	TObjectPtr<class UStaticMeshComponent> ItemMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SkillActionData)
	TObjectPtr<class UJHItemDataAsset> ItemData;

	UPROPERTY()
	TObjectPtr<class USphereComponent> TriggerSphere;

	bool IsTaked = false;
	bool IsStarted = false;
	float DistanceToOverlappingActor;
	AActor* OverlappingActor;

public:
	FORCEINLINE const float GetDistanceToOverlappingActor() { return DistanceToOverlappingActor; }

public:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	FORCEINLINE class UJHItemDataAsset* GetItemData() { return ItemData; }
	FORCEINLINE void SetItemTaked() { IsTaked = true; }

public:
	virtual void SetupWorldWidget(class UJHUserWidget* WorldWidget) override;

protected:
	UPROPERTY()
	TObjectPtr<class UJHWidgetComponent> NameWidgetComponent;

	UPROPERTY()
	TSubclassOf<class UJHUserWidget> NameWidgetClass;

	UPROPERTY()
	TObjectPtr<class UBorder> NameBorder;
};
