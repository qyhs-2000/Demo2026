// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/NotifyState/ANS_PreInputWindow.h"
#include "Character/WuwaPlayerCharater.h"
#include "AbilitySystemBlueprintLibrary.h"

void UANS_PreInputWindow::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (AWuwaPlayerCharater* PC = Cast<AWuwaPlayerCharater>(MeshComp->GetOwner()))
	{
		PC->PreInputTag = FGameplayTag::EmptyTag;
		PC->bCanPreInput = true;
	}
}

void UANS_PreInputWindow::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (AWuwaPlayerCharater* PC = Cast<AWuwaPlayerCharater>(MeshComp->GetOwner()))
	{
		//PC->PreInputTag = FGameplayTag::EmptyTag;
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(PC, PC->PreInputTag,FGameplayEventData());
		PC->bCanPreInput = false;
	}
}
