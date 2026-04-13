// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Shared/GA_HitReact.h"
#include "WarriorGameplayTags.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Character/WuwaEnemyCharater.h"
#include "Kismet/KismetMathLibrary.h"
#include "DebugHelper.h"


UGA_HitReact::UGA_HitReact()
{
	AbilityTags.AddTag(WuwaGameplayTags::Shared_Ability_HitReact);
	FAbilityTriggerData TriggerData;
	TriggerData.TriggerTag = WuwaGameplayTags::Shared_Event_HitReact;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	AbilityTriggers.Add(TriggerData);
}

void UGA_HitReact::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UAnimMontage* AM_HitReact = GetHitReactMontage();
	if (!AM_HitReact)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	UAbilityTask_PlayMontageAndWait *WaitAbilityTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("PlayHitReactMontage"), AM_HitReact);
	
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetEnemyCharacterFromActorInfo()->GetActorLocation(), TriggerEventData->Instigator->GetActorLocation());
	GetEnemyCharacterFromActorInfo()->SetActorRotation(LookAtRotation);
	
	WaitAbilityTask->OnBlendOut.AddDynamic(this, &ThisClass::OnMontageCancelOrComplete);
	WaitAbilityTask->OnCompleted.AddDynamic(this, &ThisClass::OnMontageCancelOrComplete);
	WaitAbilityTask->OnInterrupted.AddDynamic(this, &ThisClass::OnMontageCancelOrComplete);
	WaitAbilityTask->OnCancelled.AddDynamic(this, &ThisClass::OnMontageCancelOrComplete);
	WaitAbilityTask->ReadyForActivation();

}

UAnimMontage* UGA_HitReact::GetHitReactMontage()
{
	if (HitReactMontages.IsEmpty())
	{
		return nullptr;
	}

	const int Montage_Index = FMath::RandRange(0, HitReactMontages.Num() - 1);
	return HitReactMontages[Montage_Index];
}
