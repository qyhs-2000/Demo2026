// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Enemy/GA_Enemy_MeleeHit_Base.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "DebugHelper.h"
UGA_Enemy_MeleeHit_Base::UGA_Enemy_MeleeHit_Base()
{
	AbilityTags.AddTag(WuwaGameplayTags::Enemy_Ability_Melee);

	
}

UAnimMontage * UGA_Enemy_MeleeHit_Base::GetRandomMontageToPlay()
{
	if (MontagesToPlay.IsEmpty())
	{
		return nullptr;
	}
	int Index = FMath::RandRange(0, MontagesToPlay.Num() - 1);
	return MontagesToPlay[Index];
}

void UGA_Enemy_MeleeHit_Base::OnAbilityActivate()
{
	UAnimMontage* MontageToPlay = GetRandomMontageToPlay();
	UAbilityTask_PlayMontageAndWait* PlayMontageAndWaitTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("Play Melee Montage"), MontageToPlay);

	PlayMontageAndWaitTask->OnBlendOut.AddUniqueDynamic(this, &ThisClass::OnMontageCancelOrComplete);
	PlayMontageAndWaitTask->OnCompleted.AddUniqueDynamic(this, &ThisClass::OnMontageCancelOrComplete);
	PlayMontageAndWaitTask->OnCancelled.AddUniqueDynamic(this, &ThisClass::OnMontageCancelOrComplete);
	PlayMontageAndWaitTask->ReadyForActivation();

	UAbilityTask_WaitGameplayEvent* WaitGameplayEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, WuwaGameplayTags::Shared_Event_MeleeHit);
	WaitGameplayEventTask->EventReceived.AddUniqueDynamic(this, &ThisClass::HandleAttackDamage);
	WaitGameplayEventTask->ReadyForActivation();
}

void UGA_Enemy_MeleeHit_Base::HandleAttackDamage(FGameplayEventData Payload)
{
	debug::Print(TEXT("Enemy Melee Hit ,Now Handling Damage"));
	if (const AActor* TargetConst = Payload.Target)
	{
		AActor* Target = const_cast<AActor*>(TargetConst);
		EWuwaSuccessType WasSuccessfulApplyed = EWuwaSuccessType::Failed;
		FGameplayEffectSpecHandle EffectSpecHandle = MakeEnemyDamageEffectSpecHandle(GE_DealDamage_Class, BaseDamageScalableFloat);
		ApplyEffectSpecHandleToTargetActor(Target,EffectSpecHandle , WasSuccessfulApplyed);

		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			Target,
			WuwaGameplayTags::Shared_Event_HitReact,
			Payload
		);
	}
}
