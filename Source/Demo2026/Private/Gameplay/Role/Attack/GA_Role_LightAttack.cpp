// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Role/Attack/GA_Role_LightAttack.h"
#include "WarriorGameplayTags.h"
#include "Kismet/KismetMathLibrary.h"
#include "Animation/AnimMontage.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Character/WuwaPlayerCharater.h"
#include "Net/UnrealNetwork.h"
#include "DebugHelper.h"
UGA_Role_LightAttack::UGA_Role_LightAttack()
{
	AbilityTags.AddTag(WuwaGameplayTags::Player_Ability_Attack_Light);
	//CancelAbilitiesWithTag.AddTag(WuwaGameplayTags::Player_Ability_Attack_Light);
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateYes;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalOnly;
}

void UGA_Role_LightAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (AWuwaPlayerCharater* Character = Cast<AWuwaPlayerCharater>(GetAvatarActorFromActorInfo()))
	{
		Character->OnMoveInput.AddUObject(this, &ThisClass::OnMoveInputReceived);
	}
	bCanBeInterrupted = false;
	//PlayComboMontage();
}

void UGA_Role_LightAttack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (AWuwaPlayerCharater* PlayerChar = Cast<AWuwaPlayerCharater>(GetAvatarActorFromActorInfo()))
	{
		PlayerChar->OnMoveInput.RemoveAll(this);
	}
	bCanBeInterrupted = false;
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	//AttackComboCount = 0;
}

void UGA_Role_LightAttack::PlayComboMontage()
{
	if (LightAttackMontages.IsEmpty())
		return;

	int32 MontageIndex = AttackComboCount % LightAttackMontages.Num();
	UAnimMontage* MontageToPlay = LightAttackMontages[MontageIndex];
	debug::Print(GetRoleCharacterInfo(), FString::Printf(TEXT("%s Play Combo Index: %d"), GetRoleCharacterInfo()->GetLocalRole() < ROLE_Authority ? TEXT("Client ") : TEXT("Server "), MontageIndex));

	if (AWuwaPlayerCharater* Character = Cast<AWuwaPlayerCharater>(GetAvatarActorFromActorInfo()))
	{
		if (Character->HasAuthority()) // 只在服务端调用Multicast
		{
			MulticastPlayMontage(MontageToPlay);
		}
	}


}

void UGA_Role_LightAttack::ResetCombo_Implementation()
{

	// 客户端请求服务端重置
	ServerResetCombo();

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

void UGA_Role_LightAttack::ServerResetCombo_Implementation()
{
	MulticastResetCombo();
}

void UGA_Role_LightAttack::MulticastResetCombo_Implementation()
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

void UGA_Role_LightAttack::MulticastPlayMontage_Implementation(UAnimMontage* MontageToPlay)
{
	PlayAnimMontage(MontageToPlay);
}

void UGA_Role_LightAttack::PlayAnimMontage(UAnimMontage* MontageToPlay)
{
	if (CurrentPlayTask)
	{
		CurrentPlayTask->EndTask();
	}
	CurrentPlayTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this,
		FName(TEXT("PlayLightAttack")),
		MontageToPlay
	);

	CurrentPlayTask->OnCompleted.AddDynamic(this, &UGA_Role_LightAttack::OnMontageCompleted);
	//CurrentPlayTask->OnInterrupted.AddDynamic(this, &UGA_Role_LightAttack::OnMontageCompleted);
	//CurrentPlayTask->OnCancelled.AddDynamic(this, &UGA_Role_LightAttack::OnMontageCompleted);

	CurrentPlayTask->ReadyForActivation();

	bComboInputAllowed = false;
	bComboQueued = false;
	AttackComboCount++;
}

bool UGA_Role_LightAttack::Server_OnInputPressed_Validate()
{
	return true;
}

void UGA_Role_LightAttack::TryContinueCombo()
{
	PlayComboMontage();

}

void UGA_Role_LightAttack::OnInputPressed()
{
	//Client
	if (GetRoleCharacterInfo()->GetLocalRole() < ROLE_Authority)
	{
		Server_OnInputPressed();
	}
	else if (bComboInputAllowed)
	{
		//debug::Print(TEXT("Combo Input accepted immediately"));
		TryContinueCombo();
	}

}

void UGA_Role_LightAttack::Server_OnInputPressed_Implementation()
{
	// 服务器端执行连击逻辑
	//if (bComboInputAllowed)
	{
		TryContinueCombo(); // 服务器播放下一次蒙太奇
	}
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
	debug::Print(FString::Printf(TEXT("  Be Interrupted Changed")));
}

void UGA_Role_LightAttack::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UGA_Role_LightAttack, AttackComboCount);
	DOREPLIFETIME(UGA_Role_LightAttack, bComboInputAllowed);
	DOREPLIFETIME(UGA_Role_LightAttack, bCanBeInterrupted);
	DOREPLIFETIME(UGA_Role_LightAttack, bComboQueued);
}
