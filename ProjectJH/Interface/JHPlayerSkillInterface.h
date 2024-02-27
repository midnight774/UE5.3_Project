// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "JHPlayerSkillInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UJHPlayerSkillInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTJH_API IJHPlayerSkillInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void QSkillNotifyAction() = 0;
	virtual void ESkillNotifyAction() = 0;
	virtual void RSkillNotifyAction() = 0;

	virtual void QSkillAttackCheck() = 0;
	virtual void ESkillAttackCheck() = 0;
	virtual void RSkillAttackCheck() = 0;

	virtual void PauseMontage() = 0;
	virtual void ResumeMontage() = 0;
};
