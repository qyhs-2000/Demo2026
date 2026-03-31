// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/DataAsset_StartUpBase.h"
#include "AbilitySystem/WuwaAbilitySystemComponent.h"
#include "Gameplay/WuwaRoleGameplayAbility.h"
void UDataAsset_StartUpBase::GiveAbilityToAbilitSystemComponent(UWuwaAbilitySystemComponent* AbilitySystem, int32 ApplyLevel)
{
	GrantAbilities(ActivateOnGivenAbilities, AbilitySystem, ApplyLevel);

	if (!StartUpGameplayEffects.IsEmpty())
	{
		for (const TSubclassOf<UGameplayEffect>& GameplayEffect : StartUpGameplayEffects)
		{
			if (!GameplayEffect) continue;
			UGameplayEffect* Effect = GameplayEffect->GetDefaultObject<UGameplayEffect>();
			AbilitySystem->ApplyGameplayEffectToSelf(Effect, ApplyLevel, AbilitySystem->MakeEffectContext());

		}
	}
}

void UDataAsset_StartUpBase::GrantAbilities(const TArray<TSubclassOf<UWuwaGameplayAbility>>& InAbilitiesToGive, UWuwaAbilitySystemComponent* AbilitySystem, int ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty())
	{
		return;
	}

	for (const TSubclassOf<UWuwaGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (!Ability) continue;
		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = AbilitySystem->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySystem->GiveAbility(AbilitySpec);
	}
}
