// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/AnimNotify_SendGAEvent.h"
#include "AbilitySystemBlueprintLibrary.h"

void UAnimNotify_SendGAEvent::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    Super::Notify(MeshComp, Animation);
    if(MeshComp)
    {
        FGameplayEventData EventData;
        UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(),EventTag,EventData);


    }

}
