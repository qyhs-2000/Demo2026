// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "WuwaAbilitySystemComponent.generated.h"

/**
 * 
 */

class UWuwaAttributeSet;

UCLASS()
class DEMO2026_API UWuwaAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	UWuwaAbilitySystemComponent();
	void OnAbilityInputPressed(FGameplayTag InputTag);
	void OnAbilityInputReleased(FGameplayTag InputTag);

	bool TryActivateAbilityByTag(FGameplayTag InTagToActivate);

	UPROPERTY()
	UWuwaAttributeSet* WuwaAttributeSet;
};
