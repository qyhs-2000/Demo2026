// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/WuwaGameplayAbility.h"
#include "GA_Attack_Base.generated.h"

/**
 * 
 */
UCLASS()
class DEMO2026_API UGA_Attack_Base : public UWuwaGameplayAbility
{
	GENERATED_BODY()
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tag")
	FGameplayTag CurrentAttackIdentifier;

	UFUNCTION()
	void OnCompleted();

	UFUNCTION()
	void OnCancelled();

	virtual void OnEndAbility() override;
private:
};
