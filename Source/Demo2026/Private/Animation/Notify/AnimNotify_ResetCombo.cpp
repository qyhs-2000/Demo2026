// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/AnimNotify_ResetCombo.h"
#include "Character/WuwaBaseCharater.h"
#include "AbilitySystem/WuwaAbilitySystemComponent.h"
#include "Gameplay/Role/Attack/GA_Role_LightAttack.h"
void UAnimNotify_ResetCombo::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (AWuwaBaseCharater* OwnerCharacter = Cast<AWuwaBaseCharater>(MeshComp->GetOwner()))
	{
		if (UWuwaAbilitySystemComponent* ASC = OwnerCharacter->GetWuwaAbilitySystemComponent())
		{
			for (auto& Spec : ASC->GetActivatableAbilities())
			{
				if (UGA_Role_LightAttack* Ability = Cast<UGA_Role_LightAttack>(Spec.GetPrimaryInstance()))
				{
					if (Ability->IsActive())
					{
						Ability->ResetCombo();
					}
				}
			}
		}
	}
}
