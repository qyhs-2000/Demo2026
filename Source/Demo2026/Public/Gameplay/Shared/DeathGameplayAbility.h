// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/WuwaGameplayAbility.h"
#include "DeathGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class DEMO2026_API UDeathGameplayAbility : public UWuwaGameplayAbility
{
	GENERATED_BODY()
public:
	UDeathGameplayAbility();
	void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);

	UAnimMontage* GetDeathMontage();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Montage")
	TArray<UAnimMontage*> DeathMontages;

	virtual void OnMontageCancelOrComplete() override;

	UAnimMontage* AM_HitReact;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
};
