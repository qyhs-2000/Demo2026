// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Role/HitPause/HitPauseRoleGameplayAbility.h"
#include "Kismet/GameplayStatics.h"
#include "WarriorGameplayTags.h"
#include "Components/TimeDilationManagerComponent.h"
#include "Character/WuwaPlayerCharater.h"
#include "DebugHelper.h"
UHitPauseRoleGameplayAbility::UHitPauseRoleGameplayAbility()
{
	AbilityTags.AddTag(WuwaGameplayTags::Player_Ability_HitPause);
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	FAbilityTriggerData TriggerData;
	TriggerData.TriggerTag = WuwaGameplayTags::Player_Event_HitPause;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	AbilityTriggers.Add(TriggerData);

	HitPause_Name = TEXT("HitPause");
}

void UHitPauseRoleGameplayAbility::OnEndAbility()
{
	RestoreTimeDurationAndEnd();
}

void UHitPauseRoleGameplayAbility::RestoreTimeDurationAndEnd()
{
	GetWorld()->GetTimerManager().ClearTimer(DelayHandle);
	if (OwnerActorWeakPtr.IsValid())
	{
		if (AWuwaBaseCharacter* PC = Cast<AWuwaBaseCharacter>(OwnerActorWeakPtr.Get()))
		{
			if (UTimeDilationManagerComponent* TMC = PC->TimeDilationManager)
			{
				TMC->RemoveTimeOverride(HitPause_Name);
			}
		}
	}
	for (auto& TargetPtr : AffectedTargets)
	{
		if (TargetPtr.IsValid())
		{
			if (AWuwaBaseCharacter* EnemyCharacter = Cast<AWuwaBaseCharacter>(TargetPtr.Get()))
			{
				if (UTimeDilationManagerComponent* TMC = EnemyCharacter->TimeDilationManager)
				{
					TMC->RemoveTimeOverride(HitPause_Name);
				}
			}
		}
	}
	AffectedTargets.Empty();
	bIsHitPause = false;
}

void UHitPauseRoleGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	AActor* Owner = GetAvatarActorFromActorInfo();
	if (Owner == nullptr)
	{
		EndAbility();
		return;
	}
	if (!bIsHitPause)
	{
		bIsHitPause = true;
		APlayerController* PC = GetActorInfo().PlayerController.Get();
		if (PC && HitImpactShakeClass)
		{
			PC->ClientStartCameraShake(HitImpactShakeClass, 1.0);
		}
	}
	OwnerActorWeakPtr = Owner;
	//Owner->CustomTimeDilation = TimeDilation;
	UTimeDilationManagerComponent* OwnerTimeManager = Owner->GetComponentByClass<UTimeDilationManagerComponent>();
	if (OwnerTimeManager)
	{
		OwnerTimeManager->AddTimeOverride(TEXT("HitPause"), TimeDilation, 100,true);
	}
	AActor* Target = TriggerEventData && !TriggerEventData->Target.IsNull() ? const_cast<AActor*>(TriggerEventData->Target.Get()) : nullptr;
	if (Target && !AffectedTargets.Contains(Target))
	{
		TargetActorWeakPtr = Target;
		AffectedTargets.Add(Target);
		//Target->CustomTimeDilation = TimeDilation;
		if (UTimeDilationManagerComponent* TargetTimeManager = Target->GetComponentByClass<UTimeDilationManagerComponent>())
		{
			TargetTimeManager->AddTimeOverride(TEXT("HitPause"), TimeDilation, 100,true);
		}
	}
	float FinalDuration = BaseDuration;
	if (TriggerEventData->EventMagnitude > 0.f)
	{
		FinalDuration = FMath::Clamp(BaseDuration * (TriggerEventData->EventMagnitude / 100.f), 0.05f, 0.25f);
	}
	TWeakObjectPtr<UHitPauseRoleGameplayAbility> WeakThis(this);
	GetWorld()->GetTimerManager().SetTimer(DelayHandle, [WeakThis]() {
			if (UHitPauseRoleGameplayAbility* StrongPtr = WeakThis.Get())
			{
				StrongPtr->K2_EndAbility();
			}
		}, FinalDuration * UGameplayStatics::GetGlobalTimeDilation(this), false);
}




