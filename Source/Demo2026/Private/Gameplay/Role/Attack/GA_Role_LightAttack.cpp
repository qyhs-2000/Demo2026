// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Role/Attack/GA_Role_LightAttack.h"

#include "Kismet/KismetMathLibrary.h"
#include "Animation/AnimMontage.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Character/WuwaPlayerCharater.h"
#include "Net/UnrealNetwork.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/WuwaAbilitySystemComponent.h"
#include "DebugHelper.h"
UGA_Role_LightAttack::UGA_Role_LightAttack()
{
	AbilityTags.AddTag(WuwaGameplayTags::Player_Ability_Attack_Light);
	
	//CancelAbilitiesWithTag.AddTag(WuwaGameplayTags::Player_Ability_Attack_Light);
	ActivationBlockedTags.AddTag(WuwaGameplayTags::Shared_Status_Falling);
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateYes;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;

}

void UGA_Role_LightAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	if (AWuwaPlayerCharater* Character = Cast<AWuwaPlayerCharater>(GetAvatarActorFromActorInfo()))
	{
		Character->OnMoveInput.AddUObject(this, &ThisClass::OnMoveInputReceived);
	}

	bCanBeInterrupted = false;

	UAbilityTask_WaitGameplayEvent* WaitGameplayEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, WuwaGameplayTags::Shared_Event_MeleeHit);
	if (WaitGameplayEvent)
	{
		WaitGameplayEvent->EventReceived.AddUniqueDynamic(this, &ThisClass::HandleDamage);
		WaitGameplayEvent->ReadyForActivation();

	}

	TryContinueCombo();
	//ServerRPCTest();
	
}

void UGA_Role_LightAttack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (AWuwaPlayerCharater* PlayerChar = Cast<AWuwaPlayerCharater>(GetAvatarActorFromActorInfo()))
	{
		PlayerChar->OnMoveInput.RemoveAll(this);
	}
	ResetAttack();
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, true, bWasCancelled);
	//AttackComboCount = 0;
}

void UGA_Role_LightAttack::PlayComboMontage()
{
	if (LightAttackMontages.IsEmpty())
		return;

	int32 MontageIndex = AttackComboCount % LightAttackMontages.Num();
	UAnimMontage* MontageToPlay = LightAttackMontages[MontageIndex];

	if (AWuwaPlayerCharater* Character = Cast<AWuwaPlayerCharater>(GetAvatarActorFromActorInfo()))
	{
		PlayAnimMontage(MontageToPlay);
	}

}

bool UGA_Role_LightAttack::CanActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags,
	FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!ActorInfo || !ActorInfo->AvatarActor.IsValid())
		return false;

	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

void UGA_Role_LightAttack::HandleDamage(FGameplayEventData EventData)
{
	if(!GetRoleCharacterInfo()->HasAuthority())
	{
		return;
	}
	
	if (const AActor* TargetConst = EventData.Target)
	{
		AActor* Target = const_cast<AActor*>(TargetConst);
		EWuwaSuccessType WasSuccessfulApplyed = EWuwaSuccessType::Failed;
		FGameplayEffectSpecHandle EffectSpecHandle = MakeRoleDamageSpecHandle(GE_DealDamage_Class, 10.f);
		ApplyEffectSpecHandleToTargetActor(Target, EffectSpecHandle, WasSuccessfulApplyed);

		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			Target,
			WuwaGameplayTags::Shared_Event_HitReact,
			EventData
		);
	}
	//debug::Print(FString::Printf(TEXT("%s apply damage to %s"), *EventData.Instigator->GetActorNameOrLabel(), *EventData.Target->GetActorNameOrLabel()));
}

void UGA_Role_LightAttack::ResetCombo()
{
	CurrentPlayTask = nullptr;
	AttackComboCount = 0;
	bComboInputAllowed = true;
	bComboQueued = false;
}

void UGA_Role_LightAttack::OnMontageCompleted()
{
	bComboInputAllowed = true;
	bComboQueued = false;
	AttackComboCount = 0;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UGA_Role_LightAttack::OnMontageInterrupted()
{
}

void UGA_Role_LightAttack::EndAttackComboAbility()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UGA_Role_LightAttack::EnableComboInput()
{
	bComboInputAllowed = true;
	if (bComboQueued)
	{
		TryContinueCombo();
	}
}

void UGA_Role_LightAttack::PlayAnimMontage(UAnimMontage* MontageToPlay)
{
	if (CurrentPlayTask)
	{
		CurrentPlayTask->EndTask();
	}

	AWuwaPlayerCharater* PC = GetRoleCharacterInfo();
	if (PC)
	{
		FVector InputVector = PC->GetLastMovementInputVector();
		if (!InputVector.IsNearlyZero())
		{
			InputVector = PC->GetLastMovementInputVector();
			FRotator InputRot = InputVector.Rotation();
			PC->SetActorRotation(FRotator(0.f, InputRot.Yaw, 0.f));
		}
	}

	CurrentPlayTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this,
		FName(TEXT("PlayLightAttack")),
		MontageToPlay
	);

	CurrentPlayTask->OnCompleted.AddDynamic(this, &UGA_Role_LightAttack::OnMontageCompleted);
	//CurrentPlayTask->OnInterrupted.AddDynamic(this, &UGA_Role_LightAttack::OnMontageCompleted);
	CurrentPlayTask->OnCancelled.AddDynamic(this, &UGA_Role_LightAttack::OnMontageCompleted);

	CurrentPlayTask->ReadyForActivation();

	bComboInputAllowed = false;
	bComboQueued = false;
	AttackComboCount++;
}

void UGA_Role_LightAttack::ResetAttack()
{
	bCanBeInterrupted = false;
	bComboInputAllowed = true;
	AttackComboCount = 0;
}

void UGA_Role_LightAttack::TryContinueCombo()
{
	PlayComboMontage();
}

void UGA_Role_LightAttack::OnInputPressed()
{
	if (!bComboInputAllowed || GetWuwaAbilitySystemComponentFromActorInfo()->HasMatchingGameplayTag(WuwaGameplayTags::Shared_Status_Falling))
	{
		//bComboQueued = true;
		return;
	}

	TryContinueCombo();
}

void UGA_Role_LightAttack::ServerRPCTest_Implementation()
{
	debug::Print(TEXT("ServerRPCTest_Implementation called"));
}


void UGA_Role_LightAttack::OnMoveInputReceived()
{
	if (bCanBeInterrupted)
	{
		CancelAttack();
	}
}

void UGA_Role_LightAttack::CancelAttack()
{
	if (CurrentPlayTask)
	{
		CurrentPlayTask->EndTask();
		CurrentPlayTask = nullptr;
	}
	CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
}

void UGA_Role_LightAttack::SetCanBeInterrupted(bool bCanInterrupted)
{
	bCanBeInterrupted = bCanInterrupted;
}

void UGA_Role_LightAttack::OnRep_ReceiveInterrupted()
{
	//debug::Print(FString::Printf(TEXT("  Be Interrupted Changed")));
}

void UGA_Role_LightAttack::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UGA_Role_LightAttack, AttackComboCount);
	DOREPLIFETIME(UGA_Role_LightAttack, bComboInputAllowed);
	DOREPLIFETIME(UGA_Role_LightAttack, bCanBeInterrupted);
	DOREPLIFETIME(UGA_Role_LightAttack, bComboQueued);
}
