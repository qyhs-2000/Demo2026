// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "WarriorGameplayTags.h"
#include <Data/EnumTypes.h>
#include "WuwaGameplayAbility.generated.h"

/**
 * 
 */

class UWuwaAbilitySystemComponent;
class AWuwaBaseCharacter;

UENUM(BlueprintType)
enum class EWuwaGameplayAbilityActivationPolicy :uint8
{
	OnTriggered,
	OnGiven
};

UCLASS()
class DEMO2026_API UWuwaGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void OnAbilityActivate() {};
	virtual void OnEndAbility() {};
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);
	void EndAbility();
	FActiveGameplayEffectHandle ApplyEffectSpecHandleToTargetActor(AActor* TargetActor, const FGameplayEffectSpecHandle& EffectSpecHandleToApply, EWuwaSuccessType& OutSuccessfulType);
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	EWuwaGameplayAbilityActivationPolicy AbilityActivationPolicy = EWuwaGameplayAbilityActivationPolicy::OnTriggered;
	UWuwaAbilitySystemComponent* GetWuwaAbilitySystemComponentFromActorInfo()const;

	UFUNCTION(BlueprintPure)
	AWuwaBaseCharacter* GetBaseCharacterActorInfo();


	UFUNCTION()
	virtual void OnMontageCancelOrComplete();

protected:
	TWeakObjectPtr<AWuwaBaseCharacter> CachedBaseCharacterActorInfo;
};
