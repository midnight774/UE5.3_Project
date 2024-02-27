// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/JHCharacterBase.h"
#include "InputActionValue.h"
#include "Interface/JHHUDWidgetInterface.h"
#include "Interface/JHPlayerSkillInterface.h"
#include "Interface/JHPlayerItemInterface.h"
#include "Interface/JHPlayerInventoryInterface.h"
#include "JHCharacterPlayer.generated.h"

/**
 * 
 */
UENUM()
enum class EPlayerControlType : uint8
{
	Shoulder,
	Quater
};

DECLARE_DELEGATE_OneParam(FOnUseItemDelegate, class UJHItemDataAsset* /*InItemData*/);

USTRUCT(BlueprintType)
struct FUseItemDelegateWrapper
{
	GENERATED_BODY()
	FUseItemDelegateWrapper() {}
	FUseItemDelegateWrapper(const FOnUseItemDelegate& InItemDelegate) : ItemDelegate(InItemDelegate) {}
	FOnUseItemDelegate ItemDelegate;
};

UCLASS()
class PROJECTJH_API AJHCharacterPlayer : public AJHCharacterBase, public IJHHUDWidgetInterface, public IJHPlayerSkillInterface, public IJHPlayerInventoryInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AJHCharacterPlayer();

protected:

	virtual void PostInitializeComponents() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void AddSkillEffectData(const FString& StrName, class UJHCharacterSkillDataAsset* Data);

//Camera Section
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent>	Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr <class USpringArmComponent> CameraArm;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	float TargetArmLengthMax = 700.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	float TargetArmLengthMin = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	float CurrentTargetArmLength = TargetArmLengthMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	float ZoomSpeed = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	FRotator TargetRotation;

	void AdjustZoom(float DeltaTime);
	void AdjustCameraRotation(float DeltaTime);
	
//Input Section
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> QSkillAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ESkillAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> RSkillAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> DashAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ZoomInAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ZoomOutAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ChangeControlAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> QuaterMouseClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> InventoryButtonAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> QuickSlotAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> InteractionAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> CheatAction;

//Control Section
public:
	UPROPERTY(EditAnywhere, Category = CharacterControl, Meta = (AllowPrivateAccess = "true"))
	TMap<EPlayerControlType, TObjectPtr<class UJHPlayerControlData>> MapControlData;

	EPlayerControlType CurrentControlType;

	virtual void SetPlayerControl(EPlayerControlType Type);
	virtual void SetPlayerControlData(class UJHPlayerControlData*);

public:
	//ChnageControl View
	void ChangeControl(const FInputActionValue& Value);

	//Shoulder View
	void ShoulderMove(const FInputActionValue& Value);
	void ShoulderLook(const FInputActionValue& Value);
	void ShoulderZoomIn(const FInputActionValue& Value);
	void ShoulderZoomOut(const FInputActionValue& Value);

	//Inventory
	void InventoryAction(const FInputActionValue& Value);

	//Attack Section
	void Attack(const FInputActionValue& Value);

	virtual void ProcessComboAttack() override;
	virtual void AttackFinish() override;
	virtual void SetDead() override;
	virtual void DestroyCallback() override;
	virtual void HitSucceededCallback() override;

	//Skill Section

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UJHSkillComponent> SkillComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = "true"))
	float QSkillMP = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = "true"))
	float ESkillMP = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Skill, Meta = (AllowPrivateAccess = "true"))
	float RSkillMP = 150.0f;

	void Execute_QSkill(const FInputActionValue& Value);
	void Execute_ESkill(const FInputActionValue& Value);
	void Execute_RSkill(const FInputActionValue& Value);

	void QSkill();
	void ESkill();
	void RSkill();

	virtual void QSkillNotifyAction() override;
	virtual void ESkillNotifyAction() override;
	virtual void RSkillNotifyAction() override;

	virtual void QSkillAttackCheck() override;
	virtual void ESkillAttackCheck() override;
	virtual void RSkillAttackCheck() override;

	virtual void PauseMontage() override;
	virtual void ResumeMontage() override;

	bool IsUsingQSkill = false;

	void	Dash(const FInputActionValue& Value);
	void SpawnDashAfterImage();

	float	DashSpeed = 1000.0f;
	float	DashTime = 0.0f;
	float	DashTimeMax = 0.3f;

	float DashEffectTime = 0.0f;
	float DashEffectTimeMax = 0.05;

	float DashCoolTime = 0.0f;
	float DashCoolTimeMax = 2.0f;
	bool bDashEnable = true;

	bool IsDashing = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SkillAnimMonage, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UParticleSystemComponent> DashEffect;

	void StartDefaultCameraShake();
	
	void DecideAttackDirection();

	//Quater View
	void QuaterMouseClick(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class AJHMouseDecalActor> MouseDecalActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SkillAnimMonage, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UParticleSystemComponent> ShieldEffect;

	void UpdateMouseDecalPos(float DeltaTime);

//Animation Section
public:
	//Skill Anmation Section

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SkillAnimMonage, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> QSkillMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SkillAnimMonage, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> ESkillMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SkillAnimMonage, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> RSkillMontage;

	virtual void AttackHitCheck() override;

//HUD Widget Section
public:
	virtual void SetupHUDWidget(class UJHHUDWidget* InHUDWidget) override;
	virtual void AddItemToQuickSlot(class UJHItemDataAsset* InItemData, int32 SlotIdx) override;
	virtual void UseQuickSlotItem(class UJHItemDataAsset* InItemData, int32 SlotIdx) override;
	virtual void SwapQuickSlotItem(const int32 Src, const int32 Dest) override;

	virtual void RemoveItemFromQuickSlot(class UJHItemDataAsset* InItemData) override;
	virtual void SetupInventoryWidget(class UJHInventoryWidget* InInventoryWidget) override;

	//Item Section
public:

	UPROPERTY()
	TArray<FUseItemDelegateWrapper> ArrUseItemAction;

	UPROPERTY()
	TObjectPtr<class UJHInventoryComponent> InventoryComponent;

	UPROPERTY()
	TObjectPtr<class UJHQuickSlotComponent> QuickSlotComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SkillAnimMonage, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UParticleSystemComponent> HealthHealEffect;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SkillAnimMonage, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UParticleSystemComponent> ManaHealEffect;

	void SetupPlayerItemDelgate();

	virtual void AddItem(const FPrimaryAssetId& ItemId) override;
	virtual void AddItem(class UJHItemDataAsset* InItemData) override;
	virtual void AddItem(class UJHItemDataAsset* InItemData, int32 Idx, int32 Cnt) override;
	virtual void UseItem(class UJHItemDataAsset* InItemData) override;
	virtual void RemoveItemFromInventory(class UJHItemDataAsset* InItemData) override;
	virtual void UsePotion(class UJHItemDataAsset* InItemData);
	virtual void UseBuffScroll(class UJHItemDataAsset* InItemData);
	virtual void AddOverlappingItem(class AJHFieldItemActor* InItemActor) override;
	virtual void RemoveOverlappingItem(class AJHFieldItemActor* InItemActor) override;

	void InteractionKeyAction(const FInputActionValue& Value);

	TArray<class AJHFieldItemActor*> ArrOverlappingItem;
	void UpdateOverlappingItemList();

	void QuickSlotBtnCallback(const FInputActionValue& Value);
	void UseQuickSlotItem(const int32 QuickSlotIdx);

protected:
	bool IsLoaded = false;

	void LoadCharacterInfo();

	bool IsCheatOn = false;
	void CheatON(const FInputActionValue& Value);
};
