// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/JHCharacterPlayer.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Player/JHPlayerControlData.h"
#include "Player/JHPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/DecalComponent.h"
#include "Actor/JHMouseDecalActor.h"
#include "MaterialDomain.h"
#include "JHCharacterSpider.h"
#include "Collision/JHCollision.h"
#include "JHCharacterEnemy.h"
#include "UI/JHHUDWidget.h"
#include "UI/JHInventoryWidget.h"
#include "CharacterStat/JHCharacterStatComponent.h"
#include "Animation/JHAnimInstance.h"
#include "Engine/TimerHandle.h"
#include "Skill/JHSkillComponent.h"
#include "Skill/JHCharacterSkillDataAsset.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"
#include "Item/JHItemDataAsset.h"
#include "Item/JHPotionItemData.h"
#include "Component/JHInventoryComponent.h"
#include "Component/JHQuickSlotComponent.h"
#include "InputCoreTypes.h"
#include "Actor/JHGhostTrailActor.h"
#include "Engine/AssetManager.h"
#include "Item/JHFieldItemActor.h"
#include "InGameData/JHDataManager.h"

AJHCharacterPlayer::AJHCharacterPlayer()
{
	CharacterName = TEXT("GreyStone");

	CurrentControlType = EPlayerControlType::Shoulder;
	//CurrentControlType = EPlayerControlType::Quater;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> GreyStoneMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Skins/Tough/Meshes/Greystone_Tough.Greystone_Tough'"));

	if (GreyStoneMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(GreyStoneMeshRef.Object);
	}

	//Mesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -97.0f), FRotator(0.0f, -90.0f, 0.0f));
	//GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetCapsuleComponent()->SetCollisionProfileName(COL_PROFILE_CAPSULE);

	//Animation

	static ConstructorHelpers::FClassFinder<UJHAnimInstance> GreyStoneAnimRef(TEXT("/Game/ParagonGreystone/Characters/Heroes/Greystone/Greystone_AnimBlueprint.Greystone_AnimBlueprint_C"));

	if (GreyStoneAnimRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(GreyStoneAnimRef.Class);
	}

	//Camera
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));

	float DefaultTargetLength = 400.0f;
	CameraArm->TargetArmLength = DefaultTargetLength;
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);

	SkillComponent = CreateDefaultSubobject<UJHSkillComponent>(TEXT("GreyStoneSkillComponent"));
	SkillComponent->SetOwner(this);

	//Input Action
	static ConstructorHelpers::FObjectFinder<UInputAction> JumpActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProectJH/Input/Actions/IA_Jump.IA_Jump'"));

	if (JumpActionRef.Object)
	{
		JumpAction = JumpActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> LookActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProectJH/Input/Actions/IA_Look.IA_Look'"));

	if (LookActionRef.Object)
	{
		LookAction = LookActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> MoveActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProectJH/Input/Actions/IA_Move.IA_Move'"));

	if (MoveActionRef.Object)
	{
		MoveAction = MoveActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> ZoomInActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProectJH/Input/Actions/IA_ZoomIn.IA_ZoomIn'"));

	if (ZoomInActionRef.Object)
	{
		ZoomInAction = ZoomInActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> ZoomOutActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProectJH/Input/Actions/IA_ZoomOut.IA_ZoomOut'"));

	if (ZoomOutActionRef.Object)
	{
		ZoomOutAction = ZoomOutActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> ChangeControlActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProectJH/Input/Actions/IA_ChangeControl.IA_ChangeControl'"));

	if (ChangeControlActionRef.Object)
	{
		ChangeControlAction = ChangeControlActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> QuaterMouseClickActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProectJH/Input/Actions/IA_QuaterMouseClick.IA_QuaterMouseClick'"));

	if (QuaterMouseClickActionRef.Object)
	{
		QuaterMouseClickAction = QuaterMouseClickActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> AttackActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProectJH/Input/Actions/IA_Attack.IA_Attack'"));

	if (AttackActionRef.Object)
	{
		AttackAction = AttackActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> QSkillActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProectJH/Input/Actions/IA_Skill_Q.IA_Skill_Q'"));

	if (QSkillActionRef.Object)
	{
		QSkillAction = QSkillActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> ESkillActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProectJH/Input/Actions/IA_Skill_E.IA_Skill_E'"));

	if (ESkillActionRef.Object)
	{
		ESkillAction = ESkillActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> RSkillActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProectJH/Input/Actions/IA_Skill_R.IA_Skill_R'"));

	if (RSkillActionRef.Object)
	{
		RSkillAction = RSkillActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> DashActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProectJH/Input/Actions/IA_Dash.IA_Dash'"));

	if (DashActionRef.Object)
	{
		DashAction = DashActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InventoryActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProectJH/Input/Actions/IA_Inventory.IA_Inventory'"));

	if (InventoryActionRef.Object)
	{
		InventoryButtonAction = InventoryActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> QuickSlotActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProectJH/Input/Actions/IA_QuickSlotAction.IA_QuickSlotAction'"));

	if (QuickSlotActionRef.Object)
	{
		QuickSlotAction = QuickSlotActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InteractionActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProectJH/Input/Actions/IA_Interaction.IA_Interaction'"));

	if (InteractionActionRef.Object)
	{
		InteractionAction = InteractionActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> CheatActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProectJH/Input/Actions/IA_EnableFinishAttack.IA_EnableFinishAttack'"));

	if (CheatActionRef.Object)
	{
		CheatAction = CheatActionRef.Object;
	}

	//ControlData
	static ConstructorHelpers::FObjectFinder<UJHPlayerControlData> ShoulderDataRef(TEXT("/Script/ProjectJH.JHPlayerControlData'/Game/ProectJH/CharacterControl/JHC_Shoulder.JHC_Shoulder'"));
	if (ShoulderDataRef.Object)
	{
		MapControlData.Add(EPlayerControlType::Shoulder, ShoulderDataRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UJHPlayerControlData> QuaterDataRef(TEXT("/Script/ProjectJH.JHPlayerControlData'/Game/ProectJH/CharacterControl/JHC_QuaterView.JHC_QuaterView'"));
	if (QuaterDataRef.Object)
	{
		MapControlData.Add(EPlayerControlType::Quater, QuaterDataRef.Object);
	}



	//FInterpTo Speed
	ZoomSpeed = 30.0f;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackMontageRef1(TEXT("/Script/Engine.AnimMontage'/Game/ParagonGreystone/Characters/Heroes/Greystone/Animations/Attack_PrimaryA_Montage.Attack_PrimaryA_Montage'"));

	if (AttackMontageRef1.Object)
	{
		ArrAttackMontage.Add(AttackMontageRef1.Object);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackMontageRef2(TEXT("/Script/Engine.AnimMontage'/Game/ParagonGreystone/Characters/Heroes/Greystone/Animations/Attack_PrimaryB_Montage.Attack_PrimaryB_Montage'"));

	if (AttackMontageRef2.Object)
	{
		ArrAttackMontage.Add(AttackMontageRef2.Object);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackMontageRef3(TEXT("/Script/Engine.AnimMontage'/Game/ParagonGreystone/Characters/Heroes/Greystone/Animations/Attack_PrimaryC_Montage.Attack_PrimaryC_Montage'"));

	if (AttackMontageRef3.Object)
	{
		ArrAttackMontage.Add(AttackMontageRef3.Object);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ESkillMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/ProectJH/Animation/Player/AM_DefenceMontage.AM_DefenceMontage'"));

	if (ESkillMontageRef.Object)
	{
		ESkillMontage = ESkillMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UJHCharacterSkillDataAsset> QSkillData1(TEXT("/Script/ProjectJH.JHCharacterSkillDataAsset'/Game/ProectJH/SkillData/GreyStoneQSkill_1.GreyStoneQSkill_1'"));

	if (QSkillData1.Object)
	{
		AddSkillEffectData(TEXT("QParticleComp1_"), QSkillData1.Object);
	}

	static ConstructorHelpers::FObjectFinder<UJHCharacterSkillDataAsset> QSkillData2(TEXT("/Script/ProjectJH.JHCharacterSkillDataAsset'/Game/ProectJH/SkillData/GreyStoneQSkill_2.GreyStoneQSkill_2'"));

	if (QSkillData2.Object)
	{
		AddSkillEffectData(TEXT("QParticleComp2_"), QSkillData2.Object);
	}
	
	static ConstructorHelpers::FObjectFinder<UJHCharacterSkillDataAsset> RSkillData1(TEXT("/Script/ProjectJH.JHCharacterSkillDataAsset'/Game/ProectJH/SkillData/GreyStoneRSkill_1.GreyStoneRSkill_1'"));

	if (RSkillData1.Object)
	{
		AddSkillEffectData(TEXT("RParticle1_"), RSkillData1.Object);
	}

	static ConstructorHelpers::FObjectFinder<UJHCharacterSkillDataAsset> RSkillData2(TEXT("/Script/ProjectJH.JHCharacterSkillDataAsset'/Game/ProectJH/SkillData/GreyStoneRSkill_2.GreyStoneRSkill_2'"));

	if (RSkillData2.Object)
	{
		AddSkillEffectData(TEXT("RParticleComp2_"), RSkillData2.Object);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> QSkillMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/ProectJH/Animation/Player/AM_QSkillMontage.AM_QSkillMontage'"));

	if (QSkillMontageRef.Object)
	{
		QSkillMontage = QSkillMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> RSkillMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/ProectJH/Animation/Player/AM_RSkillMontage.AM_RSkillMontage'"));

	if (RSkillMontageRef.Object)
	{
		RSkillMontage = RSkillMontageRef.Object;
	}

	DefenceEffect = CreateDefaultSubobject< UParticleSystemComponent>(TEXT("DefenceParticle"));
	DefenceEffect->SetupAttachment(GetMesh(), TEXT("shield_outer"));
	DefenceEffect->SetWorldScale3D(FVector(3.0f, 3.0f, 3.0f));

	static ConstructorHelpers::FObjectFinder<UParticleSystem> DefenceParticle(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonGreystone/FX/Particles/Greystone/Abilities/Deflect/FX/P_Greystone_Deflect_Remove.P_Greystone_Deflect_Remove'"));

	if (DefenceParticle.Object)
	{
		DefenceEffect->SetTemplate(DefenceParticle.Object);
		DefenceEffect->bAutoActivate = false;
	}

	DashEffect = CreateDefaultSubobject< UParticleSystemComponent>(TEXT("DashParticle"));
	DashEffect->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> DashParticle(TEXT("/Script/Engine.ParticleSystem'/Game/ProectJH/Effect/P_Skill_Telecharge_Ice_Proj_02.P_Skill_Telecharge_Ice_Proj_02'"));

	if (DashParticle.Object)
	{
		DashEffect->SetTemplate(DashParticle.Object);
		DashEffect->bAutoActivate = false;
	}

	HealthHealEffect = CreateDefaultSubobject< UParticleSystemComponent>(TEXT("HPParticle"));
	HealthHealEffect->SetupAttachment(RootComponent);
	ManaHealEffect = CreateDefaultSubobject< UParticleSystemComponent>(TEXT("MPParticle"));
	ManaHealEffect->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> HPEffectParticle(TEXT("/Script/Engine.ParticleSystem'/Game/ProectJH/Effect/P_Health_Player_Buff_Ping_01.P_Health_Player_Buff_Ping_01'"));

	if (HPEffectParticle.Object)
	{
		HealthHealEffect->SetTemplate(HPEffectParticle.Object);
		HealthHealEffect->bAutoActivate = false;
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> MPEffectParticle(TEXT("/Script/Engine.ParticleSystem'/Game/ProectJH/Effect/P_Mana_Player_Buff_Ping_00.P_Mana_Player_Buff_Ping_00'"));

	if (MPEffectParticle.Object)
	{
		ManaHealEffect->SetTemplate(MPEffectParticle.Object);
		ManaHealEffect->bAutoActivate = false;
	}

	/*static ConstructorHelpers::FObjectFinder<UAnimMontage> DeadMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/ParagonGreystone/Characters/Heroes/Greystone/Animations/Attack_PrimaryC_Montage.Attack_PrimaryC_Montage'"));

	if (DeadMontageRef.Object)
	{
		DeadMontage = DeadMontageRef.Object;
	}*/

	InventoryComponent = CreateDefaultSubobject<UJHInventoryComponent>(TEXT("InventoryComponent"));
	QuickSlotComponent = CreateDefaultSubobject<UJHQuickSlotComponent>(TEXT("QuickSlotComponent"));
}

void AJHCharacterPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AJHCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_NavWalking);
	MouseDecalActor = GetWorld()->SpawnActor<AJHMouseDecalActor>();

	TargetArmLengthMax = 1200.0f;
	TargetArmLengthMin = 600.0f;


	AJHPlayerController* PlayerController = CastChecked<AJHPlayerController>(GetController());

	if (Controller)
	{
		EnableInput(PlayerController);
	}

	SkillComponent->SetQSkillCoolTime(5.0f);
	SkillComponent->SetESkillCoolTime(3.0f);
	SkillComponent->SetRSkillCoolTime(10.0f);

	DashCoolTimeMax = 1.2f;
	DashEffect->SetWorldScale3D(FVector(0.5f, 1.0f, 2.0f));
	HealthHealEffect->SetWorldScale3D(FVector(2.0f, 2.0f, 2.0f));
	ManaHealEffect->SetWorldScale3D(FVector(2.0f, 2.0f, 2.0f));

	CameraArm->TargetOffset = FVector(0.0f, 0.0f, 90.0f);

	SetPlayerControl(CurrentControlType);
	SetupPlayerItemDelgate();
}

void AJHCharacterPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsLoaded)
	{
		LoadCharacterInfo();
	}

	//Camera Tick Section
	AdjustZoom(DeltaTime);
	AdjustCameraRotation(DeltaTime);

	if (CurrentControlType == EPlayerControlType::Quater)
	{
		UpdateMouseDecalPos(DeltaTime);
	}

	if (!bDashEnable)
	{
		DashCoolTime += DeltaTime;
		
		if (DashCoolTimeMax - DashCoolTime < KINDA_SMALL_NUMBER)
		{
			bDashEnable = true;
			DashCoolTime = 0.0f;
		}
	}

	if (IsDashing)
	{
		DashTime += DeltaTime;
		DashEffectTime += DeltaTime;

		FVector Dir = GetLastMovementInputVector();
		RootComponent->AddRelativeLocation(Dir * DashSpeed * DeltaTime);

		if (DashEffectTimeMax - DashEffectTime < KINDA_SMALL_NUMBER)
		{
			DashEffectTime = 0.0f;
			SpawnDashAfterImage();
		}

		if (DashTimeMax - DashTime < KINDA_SMALL_NUMBER)
		{
			DashEffectTime = 0.0f;
			DashTime = 0.0f;
			IsDashing = false;
		}
	}

	if (IsUsingQSkill)
	{
		FVector Dir = GetActorForwardVector();
		RootComponent->AddRelativeLocation(Dir * DashSpeed / 2.0f * DeltaTime);
	}

	if (ArrOverlappingItem.Num() > 0)
	{
		UpdateOverlappingItemList();
	}
}

void AJHCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AJHCharacterPlayer::ShoulderLook);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AJHCharacterPlayer::ShoulderMove);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AJHCharacterPlayer::Attack);
	EnhancedInputComponent->BindAction(ZoomInAction, ETriggerEvent::Triggered, this, &AJHCharacterPlayer::ShoulderZoomIn);
	EnhancedInputComponent->BindAction(ZoomOutAction, ETriggerEvent::Triggered, this, &AJHCharacterPlayer::ShoulderZoomOut);
	EnhancedInputComponent->BindAction(QuaterMouseClickAction, ETriggerEvent::Triggered, this, &AJHCharacterPlayer::QuaterMouseClick);

	EnhancedInputComponent->BindAction(QSkillAction, ETriggerEvent::Triggered, this, &AJHCharacterPlayer::Execute_QSkill);
	EnhancedInputComponent->BindAction(ESkillAction, ETriggerEvent::Triggered, this, &AJHCharacterPlayer::Execute_ESkill);
	EnhancedInputComponent->BindAction(RSkillAction, ETriggerEvent::Triggered, this, &AJHCharacterPlayer::Execute_RSkill);
	EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Triggered, this, &AJHCharacterPlayer::Dash);
	EnhancedInputComponent->BindAction(InventoryButtonAction, ETriggerEvent::Triggered, this, &AJHCharacterPlayer::InventoryAction);
	EnhancedInputComponent->BindAction(QuickSlotAction, ETriggerEvent::Triggered, this, &AJHCharacterPlayer::QuickSlotBtnCallback);
	EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Triggered, this, &AJHCharacterPlayer::InteractionKeyAction);
	EnhancedInputComponent->BindAction(CheatAction, ETriggerEvent::Triggered, this, &AJHCharacterPlayer::CheatON);
	

}

void AJHCharacterPlayer::AddSkillEffectData(const FString& StrName, UJHCharacterSkillDataAsset* Data)
{
	TArray<TObjectPtr<class UParticleSystemComponent>> ArrParticles;

	int32 Idx = 0;
	for (UParticleSystem* PS : Data->ArrEffect)
	{
		FString IdxName = StrName + FString::FromInt(Idx);
		FName Name = FName(IdxName);
		
		UParticleSystemComponent* Particle = CreateDefaultSubobject<UParticleSystemComponent>(Name);
		Particle->SetTemplate(PS);
		Particle->bAutoActivate = false;
		Particle->SetupAttachment(GetMesh(), FName(Data->ArrEffectSocketName[Idx]));

		ArrParticles.Add(Particle);
		++Idx;
	}

	if (Data->SkillType == ESkillType::Q)
	{
		SkillComponent->AddQSkillEffectData(ArrParticles);
	}

	else if (Data->SkillType == ESkillType::E)
	{

		SkillComponent->AddESkillEffectData(ArrParticles);
	}

	else if (Data->SkillType == ESkillType::R)
	{
		SkillComponent->AddRSkillEffectData(ArrParticles);
	}
	
}

void AJHCharacterPlayer::AdjustZoom(float DeltaTime)
{
	if (CurrentControlType == EPlayerControlType::Quater)
	{
		return;
	}

	if (FMath::Abs(CurrentTargetArmLength - CameraArm->TargetArmLength) > KINDA_SMALL_NUMBER)
	{
		CameraArm->TargetArmLength = FMath::FInterpTo(CameraArm->TargetArmLength, CurrentTargetArmLength, DeltaTime, ZoomSpeed);
	}	
}

void AJHCharacterPlayer::AdjustCameraRotation(float DeltaTime)
{
	if (CurrentControlType == EPlayerControlType::Quater)
	{
	}
}

void AJHCharacterPlayer::SetPlayerControl(EPlayerControlType Type)
{
	UJHPlayerControlData* NewPlayerControl = MapControlData[Type];
	check(NewPlayerControl);

	SetPlayerControlData(NewPlayerControl);

	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		UInputMappingContext* NewMappingContext = NewPlayerControl->InputMappingContext;
		if (NewMappingContext)
		{
			Subsystem->AddMappingContext(NewMappingContext, 0);
		}
	}

	CurrentControlType = Type;

	if (Type == EPlayerControlType::Shoulder)
	{
		MouseDecalActor->SetActorHiddenInGame(true);
	}

	else
	{
		MouseDecalActor->SetActorHiddenInGame(false);
	}
}

void AJHCharacterPlayer::SetPlayerControlData(UJHPlayerControlData* ControlData)
{
	// Pawn
	bUseControllerRotationYaw = ControlData->bUseControllerRotationYaw;

	CameraArm->TargetArmLength = ControlData->TargetArmLength;
	CameraArm->bInheritPitch = ControlData->bInheritPitch;
	CameraArm->bInheritYaw = ControlData->bInheritYaw;
	CameraArm->bInheritRoll = ControlData->bInheritRoll;
	
	FRotator CurrentRot = CameraArm->GetRelativeRotation();
	CameraArm->SetRelativeRotation(ControlData->RelativeRotation);

	// CharacterMovement
	GetCharacterMovement()->bOrientRotationToMovement = ControlData->bOrientRotationToMovement;
	GetCharacterMovement()->bUseControllerDesiredRotation = ControlData->bUseControllerDesiredRotation;
	GetCharacterMovement()->RotationRate = ControlData->RotationRate;
}

void AJHCharacterPlayer::ChangeControl(const FInputActionValue& Value)
{
	if (CurrentControlType == EPlayerControlType::Shoulder)
	{
		SetPlayerControl(EPlayerControlType::Quater);
	}

	else if(CurrentControlType == EPlayerControlType::Quater)
	{
		SetPlayerControl(EPlayerControlType::Shoulder);
	}
}

void AJHCharacterPlayer::ShoulderMove(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.X);
	AddMovementInput(RightDirection, MovementVector.Y);
}

void AJHCharacterPlayer::Attack(const FInputActionValue& Value)
{
	DecideAttackDirection();

	ProcessComboAttack();
}

void AJHCharacterPlayer::ProcessComboAttack()
{
	Super::ProcessComboAttack();
}

void AJHCharacterPlayer::SetDead()
{
	Super::SetDead();
}

void AJHCharacterPlayer::DestroyCallback()
{
}

void AJHCharacterPlayer::HitSucceededCallback()
{
	Super::HitSucceededCallback();

	StatComponent->HealMP(30.0f);
}

void AJHCharacterPlayer::AttackFinish()
{
	Super::AttackFinish();
}

void AJHCharacterPlayer::UpdateMouseDecalPos(float DeltaTime)
{
	AJHPlayerController* PlayerController = CastChecked<AJHPlayerController>(GetController());

	if (PlayerController)
	{
		//카메라 위치와 마우스를 지나는 Ray 얻어오기
		FVector RayOrigin, RayDir;
		PlayerController->DeprojectMousePositionToWorld(RayOrigin, RayDir);

		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;

		//플레이어의 액터 무시
		CollisionParams.AddIgnoredActor(this);

		//나중에 Collision Channel 변경 필요
		if (GetWorld()->LineTraceSingleByChannel(HitResult, RayOrigin, RayOrigin + RayDir * 10000.f, ECC_Visibility, CollisionParams))
		{
			FVector GroundLocation = HitResult.Location;
			MouseDecalActor->GetRootComponent()->SetWorldLocation(GroundLocation);
		}
	}
}

void AJHCharacterPlayer::ShoulderLook(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void AJHCharacterPlayer::ShoulderZoomIn(const FInputActionValue& Value)
{
	CurrentTargetArmLength -= 30.0f;

	if (TargetArmLengthMin - CurrentTargetArmLength > KINDA_SMALL_NUMBER)
	{
		CurrentTargetArmLength = TargetArmLengthMin;
	}
}

void AJHCharacterPlayer::ShoulderZoomOut(const FInputActionValue& Value)
{
	CurrentTargetArmLength += 30.0f;

	if (CurrentTargetArmLength - TargetArmLengthMax > KINDA_SMALL_NUMBER)
	{
		CurrentTargetArmLength = TargetArmLengthMax;
	}

}

void AJHCharacterPlayer::InventoryAction(const FInputActionValue& Value)
{
	AJHPlayerController* PlayerController = Cast<AJHPlayerController>(Controller);

	if (PlayerController)
	{
		PlayerController->SwitchInventoryVisibility();
	}

}

void AJHCharacterPlayer::Execute_QSkill(const FInputActionValue& Value)
{
	if (!SkillComponent->IsEnableQSkill())
	{
		return;
	}

	QSkill();
}

void AJHCharacterPlayer::Execute_ESkill(const FInputActionValue& Value)
{
	if(!SkillComponent->IsEnableESkill())
	{
		return;
	}

	ESkill();
}

void AJHCharacterPlayer::Execute_RSkill(const FInputActionValue& Value)
{
	if (!SkillComponent->IsEnableRSkill())
	{
		return;
	}

	RSkill();
}

void AJHCharacterPlayer::QSkill()
{
	float CurrentMP = StatComponent->GetCurrentMP();

	if (CurrentMP < QSkillMP)
	{
		return;
	}

	StatComponent->UseMP(QSkillMP);

	if (QSkillMontage)
	{
		UJHAnimInstance* AnimInst = Cast<UJHAnimInstance>(GetMesh()->GetAnimInstance());

		if (AnimInst)
		{
			DecideAttackDirection();

			AnimInst->Montage_Play(QSkillMontage, 1.f);
			SkillComponent->UseQSkill();
		}
	}
}

void AJHCharacterPlayer::ESkill()
{
	float CurrentMP = StatComponent->GetCurrentMP();

	if (CurrentMP < ESkillMP)
	{
		return;
	}

	StatComponent->UseMP(ESkillMP);

	if (ESkillMontage)
	{
		UJHAnimInstance* AnimInst = Cast<UJHAnimInstance>(GetMesh()->GetAnimInstance());

		if (AnimInst)
		{
			AnimInst->Montage_Play(ESkillMontage, 1.25f);

			SkillComponent->UseESkill();
		}
	}
}


void AJHCharacterPlayer::RSkill()
{
	float CurrentMP = StatComponent->GetCurrentMP();

	if (CurrentMP < RSkillMP)
	{
		return;
	}

	StatComponent->UseMP(RSkillMP);

	if (RSkillMontage)
	{
		UJHAnimInstance* AnimInst = Cast<UJHAnimInstance>(GetMesh()->GetAnimInstance());

		if (AnimInst)
		{
			AnimInst->Montage_Play(RSkillMontage, 1.0f);

			SkillComponent->UseRSkill();
			GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
		}
	}
}

void AJHCharacterPlayer::QSkillNotifyAction()
{
	if (IsUsingQSkill)
	{
		IsUsingQSkill = false;
	
		StartDefaultCameraShake();
	}

	else
	{
		IsUsingQSkill = true;
	}

	SkillComponent->ExecuteQSkillData();
}

void AJHCharacterPlayer::ESkillNotifyAction()
{
	SkillComponent->ExecuteESkillData();
}

void AJHCharacterPlayer::RSkillNotifyAction()
{
	SkillComponent->ExecuteRSkillData();
}

void AJHCharacterPlayer::QSkillAttackCheck()
{
}

void AJHCharacterPlayer::ESkillAttackCheck()
{
}

void AJHCharacterPlayer::RSkillAttackCheck()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

	GetMesh()->SetVisibility(true);
	TArray<FOverlapResult> OutHitResults;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(Attack), false, this);
	Params.AddIgnoredActor(this);

	FVector Center = GetActorLocation();

	const float AttackRange = StatComponent->GetAttackRange() * 10.0f;
	const float AttackRadius = StatComponent->GetAttackRange() * 10.0f;
	float AttackDamage = StatComponent->GetAttack() * 2.0f;

	bool HitDetected = GetWorld()->OverlapMultiByChannel(OutHitResults, Center, FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeSphere(AttackRadius), Params);
	if (HitDetected)
	{
		FDamageEvent DamageEvent;

		for (FOverlapResult Result : OutHitResults)
		{
			Result.GetActor()->TakeDamage(AttackDamage, DamageEvent, GetController(), this);
		}
	}

	StartDefaultCameraShake();

#if ENABLE_DRAW_DEBUG

	float CapsuleHalfHeight = AttackRange * 0.5f;
	FColor DrawColor = HitDetected ? FColor::Red : FColor::Green;

	DrawDebugSphere(GetWorld(), Center, AttackRadius, 16, DrawColor, false, 0.3f);

#endif
}

void AJHCharacterPlayer::PauseMontage()
{
	UJHAnimInstance* AnimInst = Cast<UJHAnimInstance>(GetMesh()->GetAnimInstance());

	if (AnimInst)
	{
		GetMesh()->SetVisibility(false);
		AnimInst->Montage_Pause(RSkillMontage);
		SetPlayerControl(EPlayerControlType::Quater);
	}
}

void AJHCharacterPlayer::ResumeMontage()
{
	UJHAnimInstance* AnimInst = Cast<UJHAnimInstance>(GetMesh()->GetAnimInstance());

	if (AnimInst)
	{
		AnimInst->Montage_Resume(RSkillMontage);
	}
}

void AJHCharacterPlayer::QuaterMouseClick(const FInputActionValue& Value)
{
	AJHPlayerController* PlayerController = CastChecked<AJHPlayerController>(GetController());

	if (PlayerController)
	{
		//카메라 위치와 마우스를 지나는 Ray 얻어오기
		FVector RayStart, RayDirection;
		PlayerController->DeprojectMousePositionToWorld(RayStart, RayDirection);

		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;
		
		//플레이어의 액터 무시
		CollisionParams.AddIgnoredActor(this);

		//나중에 Collision Channel 변경 필요하다.
		if (GetWorld()->LineTraceSingleByChannel(HitResult, RayStart, RayStart + RayDirection * 10000.f, ECC_WorldStatic, CollisionParams))
		{
			// 교차점의 월드 좌표를 얻어옴
			FVector GroundLocation = HitResult.Location;
			RootComponent->SetWorldLocation(HitResult.Location);
			ResumeMontage();
			SetPlayerControl(EPlayerControlType::Shoulder);
		}
	}
}

void AJHCharacterPlayer::Dash(const FInputActionValue& Value)
{
	if (!bDashEnable)
	{
		return;
	}

	bDashEnable = false;

	if (GetCharacterMovement()->MovementMode == EMovementMode::MOVE_None)
	{
		return;
	}

	IsDashing = true;

	UJHAnimInstance* AnimInst = Cast<UJHAnimInstance>(GetMesh()->GetAnimInstance());

	if (AnimInst)
	{
		AnimInst->StopAllMontages(0.5f);
	}
}

void AJHCharacterPlayer::SpawnDashAfterImage()
{
	AJHGhostTrailActor* GhostEffect = GetWorld()->SpawnActor<AJHGhostTrailActor>(AJHGhostTrailActor::StaticClass());
	GhostEffect->SetGhostColor(FColor::Orange);
	GhostEffect->SetCharacterRef(this);
	GhostEffect->SetActorTransform(GetActorTransform());
	
	GhostEffect->SetMeshRelativeLocation(GetMesh()->GetRelativeLocation());
	GhostEffect->SetMeshRelativeRotation(GetMesh()->GetRelativeRotation());
	GhostEffect->SetMeshRelativeScale(GetMesh()->GetRelativeScale3D());

	GhostEffect->SetActiveGhost();
}

void AJHCharacterPlayer::StartDefaultCameraShake()
{
	AJHPlayerController* PlayerController = Cast<AJHPlayerController>(GetController());

	if (PlayerController)
	{
		PlayerController->StartDefaultCameraShake();
	}
}

void AJHCharacterPlayer::DecideAttackDirection()
{
	TArray<FOverlapResult> OutResults;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	const float DetectRange = 600.0f;//stat->GetDetectRange;

	const FVector Center = GetActorLocation();
	bool bDetected = GetWorld()->OverlapMultiByChannel(OutResults, Center, FQuat::Identity, COL_CHANNEL_ACTION, FCollisionShape::MakeSphere(DetectRange), Params);

	if (bDetected)
	{
		AJHCharacterEnemy* Target = Cast<AJHCharacterEnemy>(OutResults[0].GetActor());
		if (Target)
		{
			LookAt(Target->GetActorLocation());
		}
	}
}

void AJHCharacterPlayer::AttackHitCheck()
{
	Super::AttackHitCheck();

}

void AJHCharacterPlayer::SetupHUDWidget(UJHHUDWidget* InHUDWidget)
{
	if (InHUDWidget)
	{
		InHUDWidget->SetMaxHP(StatComponent->GetMaxHP());
		InHUDWidget->SetMaxMP(StatComponent->GetMaxMP());

		InHUDWidget->UpdateHPBar(StatComponent->GetCurrentHP());
		InHUDWidget->UpdateMPBar(StatComponent->GetCurrentMP());

		StatComponent->OnHPChanged.AddUObject(InHUDWidget, &UJHHUDWidget::UpdateHPBar);
		StatComponent->OnMPChanged.AddUObject(InHUDWidget, &UJHHUDWidget::UpdateMPBar);

		SkillComponent->OnQSkillCoolTimeChanged.AddUObject(InHUDWidget, &UJHHUDWidget::UpdateQSkillCoolTime);
		SkillComponent->OnESkillCoolTimeChanged.AddUObject(InHUDWidget, &UJHHUDWidget::UpdateESkillCoolTime);
		SkillComponent->OnRSkillCoolTimeChanged.AddUObject(InHUDWidget, &UJHHUDWidget::UpdateRSkillCoolTime);

		QuickSlotComponent->OnAddedItem.BindUObject(InHUDWidget, &UJHHUDWidget::AddItemToQuickSlot);
		QuickSlotComponent->OnUsedItem.BindUObject(InHUDWidget, &UJHHUDWidget::UseQuickSlotItem);
		QuickSlotComponent->OnAddedItems.BindUObject(InHUDWidget, &UJHHUDWidget::AddItemsToQuickSlot);
	}
}

void AJHCharacterPlayer::AddItemToQuickSlot(UJHItemDataAsset* InItemData, int32 SlotIdx)
{
	if (InItemData)
	{
		QuickSlotComponent->AddItem(InItemData, SlotIdx);
	}
}

void AJHCharacterPlayer::UseQuickSlotItem(UJHItemDataAsset* InItemData, int32 SlotIdx)
{
	if (InItemData)
	{
		if (QuickSlotComponent->UseItem(SlotIdx))
		{
			ArrUseItemAction[(int32)InItemData->GetItemType()].ItemDelegate.ExecuteIfBound(InItemData);
		}
	}
}

void AJHCharacterPlayer::SwapQuickSlotItem(const int32 Src, const int32 Dest)
{
	QuickSlotComponent->SwapItem(Src, Dest);
}

void AJHCharacterPlayer::RemoveItemFromQuickSlot(UJHItemDataAsset* InItemData)
{
	if (InItemData)
	{
		QuickSlotComponent->RemoveFromQuickSlot(InItemData);
	}
}

void AJHCharacterPlayer::SetupInventoryWidget(UJHInventoryWidget* InInventoryWidget)
{
	InventoryComponent->OnAddedItem.Unbind();
	InventoryComponent->OnUsedItem.Unbind();
	InventoryComponent->OnRemovedItem.Unbind();

	InventoryComponent->OnAddedItem.BindUObject(InInventoryWidget, &UJHInventoryWidget::AddItemToInventory);
	InventoryComponent->OnUsedItem.BindUObject(InInventoryWidget, &UJHInventoryWidget::UseItem);
	InventoryComponent->OnRemovedItem.BindUObject(InInventoryWidget, &UJHInventoryWidget::RemoveItemFromInventory);
	InventoryComponent->OnAddedItems.BindUObject(InInventoryWidget, &UJHInventoryWidget::AddItemsToInventory);
}

void AJHCharacterPlayer::SetupPlayerItemDelgate()
{
	ArrUseItemAction.SetNum((int32)EItemType::End);

	ArrUseItemAction[(int32)EItemType::Potion].ItemDelegate.BindUObject(this, &AJHCharacterPlayer::UsePotion);
	ArrUseItemAction[(int32)EItemType::BuffScroll].ItemDelegate.BindUObject(this, &AJHCharacterPlayer::UseBuffScroll);
}

void AJHCharacterPlayer::AddItem(const FPrimaryAssetId& ItemId)
{
	
}

void AJHCharacterPlayer::AddItem(UJHItemDataAsset* InItemData)
{
	if (InItemData)
	{
		if (QuickSlotComponent->IsEnableAddToQuickSlot(InItemData))
		{
			QuickSlotComponent->AddItem(InItemData);
		}

		else
		{
			InventoryComponent->AddItem(InItemData);
		}
	}
}

void AJHCharacterPlayer::AddItem(UJHItemDataAsset* InItemData, int32 Idx, int32 Cnt)
{
	if (InItemData)
	{
		InventoryComponent->AddItem(InItemData, Idx, Cnt);
	}
}

void AJHCharacterPlayer::UseItem(UJHItemDataAsset* InItemData)
{
	if (InItemData)
	{
		if (InventoryComponent->UseItem(InItemData))
		{
			ArrUseItemAction[(int32)InItemData->GetItemType()].ItemDelegate.ExecuteIfBound(InItemData);
		}
	}
}

void AJHCharacterPlayer::RemoveItemFromInventory(UJHItemDataAsset* InItemData)
{
	if (InItemData)
	{
		InventoryComponent->RemoveFromInventory(InItemData);
	}
}

void AJHCharacterPlayer::UsePotion(UJHItemDataAsset* InItemData)
{
	UJHPotionItemData* PotionData = Cast<UJHPotionItemData>(InItemData);

	if (PotionData)
	{
		int32 HPData = PotionData->GetHealHP();
		int32 MPData = PotionData->GetHealMP();

		if (HPData >= MPData)
		{
			HealthHealEffect->Activate(true);
		}

		else
		{
			ManaHealEffect->Activate(true);
		}

		StatComponent->HealHP(HPData);
		StatComponent->HealMP(MPData);
	}
}

void AJHCharacterPlayer::UseBuffScroll(UJHItemDataAsset* InItemData)
{
}

void AJHCharacterPlayer::AddOverlappingItem(AJHFieldItemActor* InItemActor)
{
	ArrOverlappingItem.Add(InItemActor);
}

void AJHCharacterPlayer::RemoveOverlappingItem(AJHFieldItemActor* InItemActor)
{
	ArrOverlappingItem.Remove(InItemActor);
}

void AJHCharacterPlayer::InteractionKeyAction(const FInputActionValue& Value)
{
	int32 ItemCnt = ArrOverlappingItem.Num();
	if (ArrOverlappingItem.Num() > 0)
	{
		AJHFieldItemActor* ItemActor = ArrOverlappingItem[ItemCnt - 1];
		AddItem(ItemActor->GetItemData());
		ItemActor->SetItemTaked();
	}
}

void AJHCharacterPlayer::UpdateOverlappingItemList()
{
	Algo::Sort(ArrOverlappingItem, [](class AJHFieldItemActor* Src, class AJHFieldItemActor* Dest)
		{
			return Src->GetDistanceToOverlappingActor() > Dest->GetDistanceToOverlappingActor();
		});

	/*ArrOverlappingItem.Sort([](class AJHFieldItemActor* Src, class AJHFieldItemActor* Dest)
		{
			return Src->GetDistanceToOverlappingActor() > Dest->GetDistanceToOverlappingActor();
		}
	);*/

	int32 ItemCnt = ArrOverlappingItem.Num();
	for (int32 i = 0; i < ItemCnt - 1; ++i)
	{
		ArrOverlappingItem[i]->SetSelected(false);
	}

	ArrOverlappingItem[ItemCnt - 1]->SetSelected(true);
}

void AJHCharacterPlayer::QuickSlotBtnCallback(const FInputActionValue& Value)
{
	int32 QuickSlotNum = (int32)(Value.Get<float>() + 0.1f);
	UseQuickSlotItem(QuickSlotNum - 1);
}

void AJHCharacterPlayer::UseQuickSlotItem(const int32 QuickSlotIdx)
{
	UJHItemDataAsset* Item = QuickSlotComponent->GetSlotItem(QuickSlotIdx);
	if (Item != nullptr)
	{
		UseQuickSlotItem(Item, QuickSlotIdx);
	}
		
}

void AJHCharacterPlayer::LoadCharacterInfo()
{
	UJHDataManager* DataManager = UJHDataManager::GetInst();

	DataManager->LoadCharacterItemData(InventoryComponent, QuickSlotComponent);
	DataManager->LoadCharacterStat(StatComponent);
	IsLoaded = true;
}

void AJHCharacterPlayer::CheatON(const FInputActionValue& Value)
{
	IsCheatOn = true;
	StatComponent->SetAttack(90000.0f);
}

