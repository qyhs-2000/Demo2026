// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/AnimNotify_CanInterrupt.h"
#include "Character/WuwaBaseCharater.h"
#include "AbilitySystem/WuwaAbilitySystemComponent.h"
#include "Gameplay/Role/Attack/GA_Role_LightAttack.h"
#include "Gameplay/Role/GA_Role_Dodge.h"

void UAnimNotify_CanInterrupt::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
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
						Ability->SetCanBeInterrupted(true);
					}
				}
				if (UGA_Role_Dodge* Ability = Cast<UGA_Role_Dodge>(Spec.GetPrimaryInstance()))
				{
					if (Ability->IsActive())
					{
						Ability->CancelDodge();
					}
				}
			}
		}
	}
}
