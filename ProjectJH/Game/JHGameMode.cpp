// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/JHGameMode.h"
#include "Player/JHPlayerController.h"
#include "Character/JHCharacterPlayer.h"

AJHGameMode::AJHGameMode()
{
	/*static ConstructorHelpers::FClassFinder<APawn> DefaultPawnRef(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Skins/Tough/Meshes/Greystone_Tough.Greystone_Tough'"));
	
	if (DefaultPawnRef.Class)
	{
		DefaultPawnClass = DefaultPawnRef.Class;
	}*/

	DefaultPawnClass = AJHCharacterPlayer::StaticClass();

	PlayerControllerClass = AJHPlayerController::StaticClass();
}
