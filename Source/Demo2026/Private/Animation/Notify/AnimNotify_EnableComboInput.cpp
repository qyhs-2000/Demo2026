// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/AnimNotify_EnableComboInput.h"
#include "Character/WuwaBaseCharater.h"
#include "AbilitySystem/WuwaAbilitySystemComponent.h"
#include "Gameplay/Role/Attack/GA_Role_LightAttack.h"
void UAnimNotify_EnableComboInput::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);

    // 关键：仅在服务器（权威角色）执行逻辑
    if (MeshComp && MeshComp->GetOwnerRole() == ROLE_Authority)
    {
        if (AWuwaBaseCharacter* OwnerCharacter = Cast<AWuwaBaseCharacter>(MeshComp->GetOwner()))
        {
            if (UWuwaAbilitySystemComponent* ASC = OwnerCharacter->GetWuwaAbilitySystemComponent())
            {
                for (auto& Spec : ASC->GetActivatableAbilities())
                {
                    if (UGA_Role_LightAttack* Ability = Cast<UGA_Role_LightAttack>(Spec.GetPrimaryInstance()))
                    {
                        if (Ability->IsActive()) // 确保能力正在激活中
                        {
                            Ability->EnableComboInput(); // 服务器端更新bComboInputAllowed
                            UE_LOG(LogTemp, Log, TEXT("Server: Enable combo input")); // 调试日志
                        }
                    }
                }
            }
        }
    }
}
