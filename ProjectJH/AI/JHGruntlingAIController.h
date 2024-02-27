// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/JHAIController.h"
#include "JHGruntlingAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTJH_API AJHGruntlingAIController : public AJHAIController
{
	GENERATED_BODY()
	
public:
	AJHGruntlingAIController();

public:
	void RunAI();
	void StopAI();

	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;
	virtual void UseSkill();

	FORCEINLINE bool IsSkillEnable() { return bSkillEnable; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SkillInfo, Meta = (AllowPrivateAccess = "true"))
	float	SkillCoolTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SkillInfo, Meta = (AllowPrivateAccess = "true"))
	float	SkillCoolTimeMax;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SkillInfo, Meta = (AllowPrivateAccess = "true"))
	uint8	bSkillEnable : 1;

};
