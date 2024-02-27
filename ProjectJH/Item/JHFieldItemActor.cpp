// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/JHFieldItemActor.h"
#include "Item/JHItemDataAsset.h"
#include "Components/SphereComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UI/JHWidgetComponent.h"
#include "UI/JHUserWidget.h"
#include "Interface/JHPlayerInventoryInterface.h"
#include "Collision/JHCollision.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Engine/AssetManager.h"

// Sets default values
AJHFieldItemActor::AJHFieldItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ItemSceneComp"));
	SetRootComponent(RootSceneComponent);

	ItemMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComp"));
	ItemMeshComp->SetupAttachment(RootSceneComponent);

	TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("ItemTriggerSphere"));
	TriggerSphere->SetupAttachment(RootSceneComponent);
	TriggerSphere->SetSphereRadius(100.0f);
	TriggerSphere->SetCollisionProfileName(TEXT("NoCollision"));

	NameWidgetComponent = CreateDefaultSubobject<UJHWidgetComponent>(TEXT("ItemWidgetComponent"));
	NameWidgetComponent->SetupAttachment(ItemMeshComp);
	NameWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 60.0f));

	ConstructorHelpers::FClassFinder<UJHUserWidget> NameWidgetClassRef(TEXT("/Game/ProectJH/UI/WBP_ItemName.WBP_ItemName_C"));

	if (NameWidgetClassRef.Class)
	{
		NameWidgetClass = NameWidgetClassRef.Class;

		NameWidgetComponent->SetWidgetClass(NameWidgetClass);
		NameWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
		NameWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

// Called when the game starts or when spawned
void AJHFieldItemActor::BeginPlay()
{
	Super::BeginPlay();
	
	UUserWidget* NameWidget = NameWidgetComponent->GetWidget();
	NameBorder = Cast<UBorder>(NameWidget->GetWidgetFromName(TEXT("ItemBorder")));		

	ItemMeshComp->SetCollisionProfileName(TEXT("NoCollision"));

	TriggerSphere->SetCollisionProfileName(COL_PROFILE_TRIGGER);
	TriggerSphere->InitSphereRadius(150.0f);

	SetActorScale3D(FVector(2.0f, 2.0f, 2.0f));

	UAssetManager& Manager = UAssetManager::Get();

	TArray<FPrimaryAssetId> Assets;
	Manager.GetPrimaryAssetIdList(TEXT("JHItemData"), Assets);
	ensure(0 < Assets.Num());

	int32 RandomIndex = FMath::RandRange(0, Assets.Num() - 1);
	FSoftObjectPtr AssetPtr(Manager.GetPrimaryAssetPath(Assets[RandomIndex]));

	if (AssetPtr.IsPending())
	{
		AssetPtr.LoadSynchronous();
	}
	
	UJHItemDataAsset* Item = Cast<UJHItemDataAsset>(AssetPtr.Get());
	SetItemData(Item);

	TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &AJHFieldItemActor::OnOverlapBegin);
	TriggerSphere->OnComponentEndOverlap.AddDynamic(this, &AJHFieldItemActor::OnOverlapEnd);
}

// Called every frame
void AJHFieldItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator Rot(0.0f, 30.0f * DeltaTime, 0.0f);
	ItemMeshComp->AddRelativeRotation(Rot);

	if (OverlappingActor)
	{
		FVector ItemPos = GetActorLocation();
		FVector OverlappingActorPos = OverlappingActor->GetActorLocation();

		DistanceToOverlappingActor = FVector::Distance(ItemPos, OverlappingActorPos);
	}

	if (IsTaked)
	{
		Destroy();
	}
}

void AJHFieldItemActor::SetItemData(UJHItemDataAsset* InItemData)
{
	ItemData = InItemData;

	UJHUserWidget* NameWidget = Cast<UJHUserWidget>(NameWidgetComponent->GetWidget());
	if (NameWidget)
	{
		UTextBlock* ItemNameText = Cast<UTextBlock>(NameWidget->GetWidgetFromName(TEXT("ItemNameText")));
		ItemNameText->SetText(FText::FromName(ItemData->GetItemName()));
	}

	SetupItemActor();
}

void AJHFieldItemActor::SetupItemActor()
{
	ItemMeshComp->SetStaticMesh(ItemData->GetItemMesh());
}

void AJHFieldItemActor::SetGroundLocation()
{
	FHitResult OutHit;
	FVector Start = GetActorLocation();
	FVector End = Start - FVector::UpVector * 1000.f;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams);

	if (OutHit.bBlockingHit) {
		FVector NewLocation = OutHit.ImpactPoint;
		SetActorLocation(NewLocation);
	}
}

void AJHFieldItemActor::SetSelected(bool bSelected)
{
	check(NameBorder);

	if (bSelected)
	{
		NameBorder->SetBrushColor(FColor::Orange);
	}

	else
	{
		NameBorder->SetBrushColor(FLinearColor::Gray);
	}

}

void AJHFieldItemActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IJHPlayerInventoryInterface* ItemInterface = Cast<IJHPlayerInventoryInterface>(OtherActor);

	if (ItemInterface)
	{
		ItemInterface->AddOverlappingItem(this);
		OverlappingActor = OtherActor;
	}
}

void AJHFieldItemActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	IJHPlayerInventoryInterface* ItemInterface = Cast<IJHPlayerInventoryInterface>(OtherActor);

	if (ItemInterface)
	{
		ItemInterface->RemoveOverlappingItem(this);
		OverlappingActor = nullptr;
		DistanceToOverlappingActor = 1000.0f;
		SetSelected(false);
	}
}

void AJHFieldItemActor::SetupWorldWidget(UJHUserWidget* WorldWidget)
{
	UTextBlock* ItemTextWidget = Cast<UTextBlock>(WorldWidget->GetWidgetFromName(TEXT("ItemNameText")));

	if (ItemTextWidget)
	{
		ItemTextWidget->SetText(FText::FromName(ItemData->GetItemName()));
	}

	NameWidgetComponent->SetWidget(WorldWidget);
}

