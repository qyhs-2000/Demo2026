// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/WuwaRoleGameplayAbility.h"
#include "Character/WuwaPlayerCharater.h"

AWuwaPlayerCharater* UWuwaRoleGameplayAbility::GetRoleCharacterInfo()
{
    if (!CachedRoleCharacterInfo.IsValid())
    {
        CachedRoleCharacterInfo = Cast<AWuwaPlayerCharater>(CurrentActorInfo->AvatarActor);
    }
    return CachedRoleCharacterInfo.IsValid() ? CachedRoleCharacterInfo.Get() : nullptr;
}
