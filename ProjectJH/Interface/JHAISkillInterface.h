// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "JHAISkillInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UJHAISkillInterface : public UInterface
{
	GENERATED_BODY()
};

DECLARE_DELEGATE(FAISkillFinishedDelegate)
DECLARE_DELEGATE(FAISkillCallbackDelegate)

USTRUCT()
struct FSkillMontages
{
	GENERATED_BODY()
	TArray<FAISkillCallbackDelegate> SkillCallbackDelegate;
	TArray<TObjectPtr<class UAnimMontage>> SkillMontages;
	int32 CurrentMontageIdx = 0;
};

/**
 * 
 */
class PROJECTJH_API IJHAISkillInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void ExecuteAISkill(const int32 SkillIdx) = 0;
	virtual void ProcessRageSkill() = 0;
	virtual void ProcessSkill() = 0;
	virtual void SkillFinished() = 0;
	virtual void SetAISkillFinishedDelegate(const FAISkillFinishedDelegate& Delegate) = 0;
	virtual void SetCharacterPause() = 0;
};
