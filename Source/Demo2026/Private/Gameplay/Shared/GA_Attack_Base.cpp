// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Shared/GA_Attack_Base.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Character/WuwaBaseCharater.h"
#include "DataAssets/Role/DataAsset_RoleAttack.h"
#include "AbilitySystem/WuwaAbilitySystemComponent.h"

void UGA_Attack_Base::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

   
    
    if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
        return;
    }

    AWuwaBaseCharacter* Character = GetBaseCharacterActorInfo();
    if (!Character || !Character->GetCombatDataAsset())
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
        return;
    }

    if (UWuwaAbilitySystemComponent * ASC = Character->GetWuwaAbilitySystemComponent())
    {
        if (!ASC->HasMatchingGameplayTag(WuwaGameplayTags::Shared_State_IsAttacking))
        {
            ASC->AddLooseGameplayTag(WuwaGameplayTags::Shared_State_IsAttacking);
        }

         if (ASC->HasMatchingGameplayTag(WuwaGameplayTags::Shared_ComboWindow))
        {
            int32 Count = ASC->GetGameplayTagCount(WuwaGameplayTags::Shared_ComboWindow);
            ASC->RemoveLooseGameplayTags(FGameplayTagContainer(WuwaGameplayTags::Shared_ComboWindow), Count);
        }
    }

    const UDataAsset_RoleAttack* CombatDataAsset = Character->GetCombatDataAsset();
    if (const FAttackDataNode* AttackNode = CombatDataAsset->AttackNodes.Find(CurrentAttackIdentifier))
    {
        UAnimMontage* MontageToPlay = AttackNode->AttackMontage;
        UAbilityTask_PlayMontageAndWait* Task = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, MontageToPlay);
        Task->OnCompleted.AddDynamic(this, &ThisClass::OnCompleted);
        Task->OnCancelled.AddDynamic(this, &ThisClass::OnCancelled);
        Task->ReadyForActivation();
    }
    else
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
    }

}

void UGA_Attack_Base::OnCompleted()
{
    EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
}

void UGA_Attack_Base::OnCancelled()
{
    EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
}

void UGA_Attack_Base::OnEndAbility()
{
    AWuwaBaseCharacter* Character = GetBaseCharacterActorInfo();
    if (!Character)
    {
        return;
    }

    if (UWuwaAbilitySystemComponent * ASC = Character->GetWuwaAbilitySystemComponent())
    {
        if (ASC->HasMatchingGameplayTag(WuwaGameplayTags::Shared_State_IsAttacking))
        {
            ASC->RemoveLooseGameplayTag(WuwaGameplayTags::Shared_State_IsAttacking);
        }

        // if (ASC->HasMatchingGameplayTag(WuwaGameplayTags::Shared_ComboWindow))
        // {
        //     int32 Count = ASC->GetGameplayTagCount(WuwaGameplayTags::Shared_ComboWindow);
        //     ASC->RemoveLooseGameplayTags(FGameplayTagContainer(WuwaGameplayTags::Shared_ComboWindow), Count);
        // }
    }
}
