// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Role/GA_Role_Dodge.h"
#include "WarriorGameplayTags.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Character/WuwaPlayerCharater.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "AbilitySystemBlueprintLibrary.h"

UGA_Role_Dodge::UGA_Role_Dodge()
{
	AbilityTags.AddTag(WuwaGameplayTags::Player_Ability_Dodge);
	CancelAbilitiesWithTag.AddTag(WuwaGameplayTags::Player_Ability_Attack_Light);
	//ActivationOwnedTags.AddTag(WuwaGameplayTags::Shared_Status_Invincible);
	ActivationOwnedTags.AddTag(WuwaGameplayTags::Player_Status_Dodging);
}

void UGA_Role_Dodge::OnAbilityActivate()
{
	if (!AM_MoveBack)
	{
		EndAbility();
		return;
	}

	AWuwaPlayerCharater* PC = GetRoleCharacterInfo();
	if (!PC)
	{
		EndAbility();
	}

	UAbilityTask_WaitGameplayEvent* WaitGameplayEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, WuwaGameplayTags::Player_Event_OnPerfectDodgeTrigger, nullptr, true);
	WaitGameplayEventTask->EventReceived.AddUniqueDynamic(this, &ThisClass::OnPerfectDodgeTrigger);
	WaitGameplayEventTask->ReadyForActivation();

	UAnimMontage* MontageToPlay = nullptr;
	FVector InputVector = PC->GetPendingMovementInputVector();
	if (InputVector.IsNearlyZero())
	{
		InputVector = PC->GetLastMovementInputVector();
	}
	if (InputVector.IsNearlyZero())
	{
		MontageToPlay = AM_MoveBack;
	}
	else
	{
		FRotator InputRot = InputVector.Rotation();
		PC->SetActorRotation(FRotator(0.f, InputRot.Yaw, 0.f));
		MontageToPlay = AM_MoveForward;
	}

	CurrentPlayTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("Play Dodge Anim"), MontageToPlay);
	CurrentPlayTask->OnCompleted.AddUniqueDynamic(this, &ThisClass::OnMontageCancelOrComplete);
	CurrentPlayTask->ReadyForActivation();

}

void UGA_Role_Dodge::OnPerfectDodgeTrigger(FGameplayEventData Payload)
{
	AWuwaPlayerCharater* PC = GetRoleCharacterInfo();
	bool IsMoving = PC->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f;
	UAnimMontage* PerfectMontage = IsMoving ? AM_DodgeForward : AM_DodgeBack;
	if (CurrentPlayTask)
	{
		CurrentPlayTask->EndTask();
	}
	CurrentPlayTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("Play Dodge Anim"), PerfectMontage);
	CurrentPlayTask->OnCompleted.AddUniqueDynamic(this, &ThisClass::OnMontageCancelOrComplete);
	CurrentPlayTask->ReadyForActivation();

	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	if (ASC && !ASC->HasMatchingGameplayTag(WuwaGameplayTags::Player_State_Cooldown_SuperMatrix))
	{
		FGameplayEventData EventData;
		EventData.Instigator = PC;
		EventData.Target = PC;
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(PC, WuwaGameplayTags::Player_Event_TriggerSuperMatrix, EventData);

	}

}

void UGA_Role_Dodge::CancelDodge()
{
	CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false);
}
