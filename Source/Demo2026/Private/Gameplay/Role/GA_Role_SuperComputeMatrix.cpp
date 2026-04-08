// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Role/GA_Role_SuperComputeMatrix.h"
#include "WarriorGameplayTags.h"
#include "Kismet/GameplayStatics.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"
#include "Components/TimeDilationManagerComponent.h"
#include "Character/WuwaPlayerCharater.h"
#include "Components/PostProcessComponent.h"
#include "DebugHelper.h"

UGA_Role_SuperComputeMatrix::UGA_Role_SuperComputeMatrix()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	FAbilityTriggerData TriggerData;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	TriggerData.TriggerTag = WuwaGameplayTags::Player_Event_TriggerSuperMatrix;
	AbilityTriggers.Add(TriggerData);

	if (CooldownGE)
	{
		CooldownGameplayEffectClass = CooldownGE;

	}
	TimeEffectName = TEXT("SuperMatrix");
}

void UGA_Role_SuperComputeMatrix::OnAbilityActivate()
{

	debug::Print(TEXT("Super Compute Matrix!"));
	if (!CommitAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo()))
	{
		EndAbility();
		return;
	}

	SavedWorldDilation = UGameplayStatics::GetGlobalTimeDilation(this);
	UGameplayStatics::SetGlobalTimeDilation(this, WorldFreezeDilation);

	if (AActor* PlayerActor = GetAvatarActorFromActorInfo())
	{
		if (UTimeDilationManagerComponent* TDM = PlayerActor->FindComponentByClass<UTimeDilationManagerComponent>())
		{
			TDM->AddTimeOverride(TimeEffectName, 1.0f, 50, true);
		}

		if (AWuwaPlayerCharater* PC = GetRoleCharacterInfo())
		{
			if (PC->MatrixPostProcess)
			{
				PC->MatrixPostProcess->bEnabled = true;

			}
		}
	}
	float ActualDilation = UGameplayStatics::GetGlobalTimeDilation(this);

	float CompensatedDuration = ActivateDuration * ActualDilation;

	GetWorld()->GetTimerManager().SetTimer(
		FreezeTimeHandle,
		this,
		&UGA_Role_SuperComputeMatrix::RestoreTimeAndEnd,
		CompensatedDuration,
		false
	);



}

void UGA_Role_SuperComputeMatrix::OnEndAbility()
{
	GetWorld()->GetTimerManager().ClearTimer(FreezeTimeHandle);
	UGameplayStatics::SetGlobalTimeDilation(this, SavedWorldDilation);
	if (AActor* PlayerActor = GetAvatarActorFromActorInfo())
	{
		if (UTimeDilationManagerComponent* TDM = PlayerActor->FindComponentByClass<UTimeDilationManagerComponent>())
		{
			TDM->RemoveTimeOverride(TimeEffectName);
		}
	}

	if (AActor* PlayerActor = GetAvatarActorFromActorInfo())
	{
		if (AWuwaPlayerCharater* PC = GetRoleCharacterInfo())
		{
			if (PC->MatrixPostProcess)
			{
				PC->MatrixPostProcess->bEnabled = false;
			}
		}
	}
}

void UGA_Role_SuperComputeMatrix::RestoreTimeAndEnd()
{

	EndAbility();
}
