// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_AdjustFire.h"
#include "Interface/JHProjectileAttackInterface.h"

UAnimNotify_AdjustFire::UAnimNotify_AdjustFire()
{
}

void UAnimNotify_AdjustFire::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		IJHProjectileAttackInterface* AttackInterface = Cast<IJHProjectileAttackInterface>(MeshComp->GetOwner());

		if (AttackInterface)
		{
			AttackInterface->AdjustFirePos();
		}
	}
}
