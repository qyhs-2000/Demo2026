// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpBase.generated.h"

/**
 * 
 */

class UWuwaAbilitySystemComponent;
class UWuwaGameplayAbility;
class UGameplayEffect;
UCLASS()
class DEMO2026_API UDataAsset_StartUpBase : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "StartUpData")

	/*Ö±½Ó¸³ÓèµÄability*/
	TArray<TSubclassOf<UWuwaGameplayAbility>> ActivateOnGivenAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "StartUpData")
	TArray<TSubclassOf<UGameplayEffect>> StartUpGameplayEffects;

	virtual void GiveAbilityToAbilitSystemComponent(UWuwaAbilitySystemComponent* AbilitySystem,int32 ApplyLevel = 1);
	void GrantAbilities(const TArray<TSubclassOf<UWuwaGameplayAbility>>& InAbilitiesToGive,UWuwaAbilitySystemComponent* AbilitySystem,int ApplyLevel);
};
