// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Shared/GA_CharacterJump.h"
#include "Character/WuwaPlayerCharater.h"
#include "WarriorGameplayTags.h"

UGA_CharacterJump::UGA_CharacterJump()
{
    AbilityTags.AddTag(WuwaGameplayTags::Player_Ability_Jump);
    //CancelAbilitiesWithTag.AddTag(WuwaGameplayTags::Player_Ability_Jump);
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_CharacterJump::OnAbilityActivate()
{
    if (AWuwaPlayerCharater* Character = Cast<AWuwaPlayerCharater>(GetAvatarActorFromActorInfo()))
    {
        Character->Jump();

    }

    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);

}