// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/WuwaGameplayAbility.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/WuwaAbilitySystemComponent.h"
#include "Character/WuwaBaseCharater.h"

void UWuwaGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	OnAbilityActivate();
}

void UWuwaGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	if (AbilityActivationPolicy == EWuwaGameplayAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

void UWuwaGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	OnEndAbility();
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UWuwaGameplayAbility::EndAbility()
{
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
}

FActiveGameplayEffectHandle UWuwaGameplayAbility::ApplyEffectSpecHandleToTargetActor(AActor* TargetActor, const FGameplayEffectSpecHandle& EffectSpecHandleToApply, EWuwaSuccessType& OutSuccessfulType)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	check(TargetASC);
	FActiveGameplayEffectHandle Handle = GetWuwaAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*EffectSpecHandleToApply.Data, TargetASC);

	OutSuccessfulType = Handle.IsValid() ? EWuwaSuccessType::Successful : EWuwaSuccessType::Failed;
	return Handle;
}

UWuwaAbilitySystemComponent* UWuwaGameplayAbility::GetWuwaAbilitySystemComponentFromActorInfo() const
{

	UAbilitySystemComponent* AbilitySystemComponent = CurrentActorInfo ? CurrentActorInfo->AbilitySystemComponent.Get() : nullptr;
	ensure(AbilitySystemComponent);
	return Cast<UWuwaAbilitySystemComponent>(AbilitySystemComponent);
}

AWuwaBaseCharacter* UWuwaGameplayAbility::GetBaseCharacterActorInfo()
{
	
	if (!CachedBaseCharacterActorInfo.IsValid())
	{
		CachedBaseCharacterActorInfo = Cast<AWuwaBaseCharacter>(CurrentActorInfo->AvatarActor);
	}
	return CachedBaseCharacterActorInfo.IsValid() ? CachedBaseCharacterActorInfo.Get() : nullptr;
}

void UWuwaGameplayAbility::OnMontageCancelOrComplete()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
