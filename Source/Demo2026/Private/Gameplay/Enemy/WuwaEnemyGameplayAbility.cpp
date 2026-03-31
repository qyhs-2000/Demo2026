// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Enemy/WuwaEnemyGameplayAbility.h"
#include "Character/WuwaEnemyCharater.h"
#include "AbilitySystem/WuwaAbilitySystemComponent.h"
AWuwaEnemyCharacter* UWuwaEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if (!CachedEnemyCharacter.IsValid())
	{
		CachedEnemyCharacter = Cast<AWuwaEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}
	return CachedEnemyCharacter.IsValid()?CachedEnemyCharacter.Get():nullptr;
}

FGameplayEffectSpecHandle UWuwaEnemyGameplayAbility::MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat)
{
	check(EffectClass);
	FGameplayEffectContextHandle ContextHandle = GetWuwaAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(),GetAvatarActorFromActorInfo());
	FGameplayEffectSpecHandle EffectSpecHandle = GetWuwaAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(EffectClass, GetAbilityLevel(), ContextHandle);
	EffectSpecHandle.Data->SetSetByCallerMagnitude(WuwaGameplayTags::Shared_SetByCaller_BaseDamage, InDamageScalableFloat.GetValueAtLevel(GetAbilityLevel()));
	return EffectSpecHandle;
}
