// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/AnimNotify_EnableComboInput.h"
#include "Character/WuwaBaseCharater.h"
#include "AbilitySystem/WuwaAbilitySystemComponent.h"
#include "Gameplay/Role/Attack/GA_Role_LightAttack.h"
void UAnimNotify_EnableComboInput::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);

    if (MeshComp)
    {
        if (AWuwaBaseCharacter* OwnerCharacter = Cast<AWuwaBaseCharacter>(MeshComp->GetOwner()))
        {
            if (UWuwaAbilitySystemComponent* ASC = OwnerCharacter->GetWuwaAbilitySystemComponent())
            {
                for (auto& Spec : ASC->GetActivatableAbilities())
                {
                    if (UGA_Role_LightAttack* Ability = Cast<UGA_Role_LightAttack>(Spec.GetPrimaryInstance()))
                    {
                        if (Ability->IsActive())
                        {
                            Ability->EnableComboInput(); 
                        }
                    }
                }
            }
        }
    }
}
