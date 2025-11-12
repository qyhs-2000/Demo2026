// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/DataAsset_StartUpBase.h"
#include "GameplayTagContainer.h"
#include "DataAsset_RoleStartUp.generated.h"

/**
 * 
 */

class UWuwaRoleGameplayAbility;

USTRUCT(BlueprintType)
struct FWuwaRoleInputAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UWuwaRoleGameplayAbility> AbilityToGrant;

	bool isValid()const;
};

UCLASS()
class DEMO2026_API UDataAsset_RoleStartUp : public UDataAsset_StartUpBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	TArray<FWuwaRoleInputAbilitySet> RoleStartupInputAbilitySets;

	virtual void GiveAbilityToAbilitSystemComponent(UWuwaAbilitySystemComponent* AbilitySystem ,int32 ApplyLevel = 1) override;
};
