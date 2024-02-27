
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "JHCharacterStat.generated.h"

USTRUCT(BlueprintType)
struct FJHCharacterStat : public FTableRowBase
{
	GENERATED_BODY()

public:
	FJHCharacterStat() : MaxHP(0.0f), MaxMP(0.0f), Attack(0.0f), AttackRange(0.0f), AttackSpeed(0.0f), Defence(0.0f), MoveSpeed(0.0f) {}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStat)
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStat)
	float MaxMP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStat)
	float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStat)
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStat)
	float AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStat)
	float Defence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStat)
	float MoveSpeed;

};