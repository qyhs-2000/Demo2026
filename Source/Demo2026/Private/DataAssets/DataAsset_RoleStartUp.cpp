// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/DataAsset_RoleStartUp.h"
#include "Gameplay/WuwaRoleGameplayAbility.h"
#include "AbilitySystem/WuwaAbilitySystemComponent.h"

bool FWuwaRoleInputAbilitySet::isValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}

void UDataAsset_RoleStartUp::GiveAbilityToAbilitSystemComponent(UWuwaAbilitySystemComponent* AbilitySystem,int32 ApplyLevel)
{
	Super::GiveAbilityToAbilitSystemComponent(AbilitySystem);

	for (const FWuwaRoleInputAbilitySet& AbilitySet : RoleStartupInputAbilitySets)
	{
		if (AbilitySet.isValid())
		{
			FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
			AbilitySpec.SourceObject = AbilitySystem->GetAvatarActor();
			AbilitySpec.Level = ApplyLevel;
			AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);
			AbilitySystem->GiveAbility(AbilitySpec);
		}
	}
}
