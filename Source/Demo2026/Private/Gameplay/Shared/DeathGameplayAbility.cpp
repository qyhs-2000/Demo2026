// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Shared/DeathGameplayAbility.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Character/WuwaBaseCharater.h"
#include "Controller/WuwaAIController.h"
#include "BrainComponent.h"



UDeathGameplayAbility::UDeathGameplayAbility()
{
	AbilityTags.AddTag(WuwaGameplayTags::Shared_Ability_Death);

	CancelAbilitiesWithTag.AddTag(WuwaGameplayTags::Shared_Ability_HitReact);
	BlockAbilitiesWithTag.AddTag(WuwaGameplayTags::Shared_Ability_HitReact);
	FAbilityTriggerData TriggerData;
	TriggerData.TriggerTag = WuwaGameplayTags::Shared_Status_Death;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::OwnedTagAdded;
	AbilityTriggers.Add(TriggerData);
}

void UDeathGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AWuwaAIController* EnemyAIController = Cast<AWuwaAIController>(GetBaseCharacterActorInfo()->GetController());
	if (EnemyAIController)
	{
		if (UBrainComponent* Brain = EnemyAIController->GetBrainComponent())
		{
			Brain->StopLogic(TEXT("Dead"));
		}
	}

	AM_HitReact = GetDeathMontage();
	UAbilityTask_PlayMontageAndWait* WaitAbilityTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("PlayHitReactMontage"), AM_HitReact);
	WaitAbilityTask->OnCompleted.AddDynamic(this, &ThisClass::OnMontageCancelOrComplete);
	WaitAbilityTask->OnCancelled.AddDynamic(this, &ThisClass::OnMontageCancelOrComplete);
	WaitAbilityTask->OnBlendOut.AddDynamic(this, &ThisClass::OnMontageCancelOrComplete);
	WaitAbilityTask->ReadyForActivation();

}

UAnimMontage* UDeathGameplayAbility::GetDeathMontage()
{
	if (DeathMontages.IsEmpty())
	{
		return nullptr;
	}
	int RandomIndex = FMath::RandRange(0, DeathMontages.Num() - 1);
	return DeathMontages[RandomIndex];
}

void UDeathGameplayAbility::OnMontageCancelOrComplete()
{

	Super::OnMontageCancelOrComplete();
}

void UDeathGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (AWuwaBaseCharacter* Character = Cast<AWuwaBaseCharacter>(GetBaseCharacterActorInfo()))
	{
		Character->OnCharacterDeath();
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
