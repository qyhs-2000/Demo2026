// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/WuwaAbilitySystemComponent.h"
#include "Gameplay/Role/Attack/GA_Role_LightAttack.h"

void UWuwaAbilitySystemComponent::OnAbilityInputPressed(FGameplayTag InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag)) continue;

		if (AbilitySpec.IsActive())
		{
			
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
			}
		}
	}
}

void UWuwaAbilitySystemComponent::OnAbilityInputReleased(FGameplayTag InputTag)
{
}
