// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/NotifyState/ANS_ComboWindow.h"
#include "Character/WuwaBaseCharater.h"
#include "AbilitySystem/WuwaAbilitySystemComponent.h"
#include "WarriorGameplayTags.h"

void UANS_ComboWindow::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (AWuwaBaseCharacter* BaseChar = Cast<AWuwaBaseCharacter>(MeshComp->GetOwner()))
	{
		if (UWuwaAbilitySystemComponent* ASC = BaseChar->GetWuwaAbilitySystemComponent())
		{
			ASC->AddLooseGameplayTag(WuwaGameplayTags::Shared_ComboWindow);
		}
	}
}

void UANS_ComboWindow::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (AWuwaBaseCharacter* BaseChar = Cast<AWuwaBaseCharacter>(MeshComp->GetOwner()))
	{
		if (UWuwaAbilitySystemComponent* ASC = BaseChar->GetWuwaAbilitySystemComponent())
		{
			ASC->RemoveLooseGameplayTag(WuwaGameplayTags::Shared_ComboWindow);
		}
	}
}
