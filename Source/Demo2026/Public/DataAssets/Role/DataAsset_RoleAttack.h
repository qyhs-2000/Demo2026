// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "DataAsset_RoleAttack.generated.h"

/**
 * 
 */

class UGA_Attack_Base;


USTRUCT(BlueprintType)
struct FAttackDataNode
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<UGA_Attack_Base> AbilityClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* AttackMontage;

};


UCLASS(BlueprintType)
class DEMO2026_API UDataAsset_RoleAttack : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FGameplayTag, FAttackDataNode> AttackNodes;
};
