// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/WuwaRoleGameplayAbility.h"
#include "Character/WuwaPlayerCharater.h"
#include "AbilitySystem/WuwaAbilitySystemComponent.h"
#include "Controller/WuwaPlayerController.h"
#include "WarriorGameplayTags.h"

AWuwaPlayerCharater* UWuwaRoleGameplayAbility::GetRoleCharacterInfo()
{
    if (!CachedRoleCharacterInfo.IsValid())
    {
        CachedRoleCharacterInfo = Cast<AWuwaPlayerCharater>(CurrentActorInfo->AvatarActor);
    }
    return CachedRoleCharacterInfo.IsValid() ? CachedRoleCharacterInfo.Get() : nullptr;
}

FGameplayEffectSpecHandle UWuwaRoleGameplayAbility::MakeRoleDamageSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InBaseDamage)
{
    check(EffectClass);
    FGameplayEffectContextHandle ContextHandle = GetWuwaAbilitySystemComponentFromActorInfo()->MakeEffectContext();
    ContextHandle.SetAbility(this);
    ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
    ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());
    FGameplayEffectSpecHandle EffectSpecHandle = GetWuwaAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(EffectClass, GetAbilityLevel(), ContextHandle);
    EffectSpecHandle.Data->SetSetByCallerMagnitude(WuwaGameplayTags::Shared_SetByCaller_BaseDamage, InBaseDamage);
    return EffectSpecHandle;
}

AWuwaPlayerController* UWuwaRoleGameplayAbility::GetRoleControllerFromActorInfo()
{
    
    return Cast<AWuwaPlayerController>(GetRoleCharacterInfo()->GetController());
}


