// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_FireProjectile.h"
#include "Interface/JHProjectileAttackInterface.h"

UAnimNotify_FireProjectile::UAnimNotify_FireProjectile()
{
}

void UAnimNotify_FireProjectile::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		IJHProjectileAttackInterface* AttackInterface = Cast<IJHProjectileAttackInterface>(MeshComp->GetOwner());

		if (AttackInterface)
		{
			AttackInterface->FireProjectile();
		}
	}
}
