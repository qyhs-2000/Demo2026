// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/WuwaAbilitySystemComponent.h"
#include "AbilitySystem/WuwaAttributeSet.h"
#include "WarriorGameplayTags.h"
#include "Gameplay/Role/Attack/GA_Role_LightAttack.h"

UWuwaAbilitySystemComponent::UWuwaAbilitySystemComponent()
{
}

void UWuwaAbilitySystemComponent::OnAbilityInputPressed(FGameplayTag InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}

	const auto& Abilities = GetActivatableAbilities();
	for (const FGameplayAbilitySpec& AbilitySpec : Abilities)
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag)) continue;


		if (InputTag.MatchesTag(WuwaGameplayTags::InputTag_Toggleable) && AbilitySpec.IsActive())
		{
			CancelAbilityHandle(AbilitySpec.Handle);
		}
		// first activate
		else
		{
			TryActivateAbility(AbilitySpec.Handle);

		}

		if (UGameplayAbility* ActiveAbility = AbilitySpec.GetPrimaryInstance())
		{
			if (UGA_Role_LightAttack* AttackAbility = Cast<UGA_Role_LightAttack>(ActiveAbility))
			{
				AttackAbility->OnInputPressed();
				return;
			}
		}
	}
}

void UWuwaAbilitySystemComponent::OnAbilityInputReleased(FGameplayTag InputTag)
{
}

bool UWuwaAbilitySystemComponent::TryActivateAbilityByTag(FGameplayTag InTagToActivate)
{
	check(InTagToActivate.IsValid());
	TArray<FGameplayAbilitySpec*> AbilitySpecs;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(InTagToActivate.GetSingleTagContainer(), AbilitySpecs);
	if (!AbilitySpecs.IsEmpty())
	{
		const int RandomIndex = FMath::RandRange(0, AbilitySpecs.Num() - 1);
		FGameplayAbilitySpec* AbilitySpecToActivate = AbilitySpecs[RandomIndex];
		check(AbilitySpecToActivate);

		if (!AbilitySpecToActivate->IsActive())
		{
			return TryActivateAbility(AbilitySpecToActivate->Handle);
		}
	}
	return false;
}
