// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/WuwaRoleGameplayAbility.h"
#include "HitPauseRoleGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class DEMO2026_API UHitPauseRoleGameplayAbility : public UWuwaRoleGameplayAbility
{
	GENERATED_BODY()
public:
	UHitPauseRoleGameplayAbility();
	virtual void OnEndAbility() override;
	void RestoreTimeDurationAndEnd();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float TimeDilation = 0.2f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float BaseDuration = 0.1f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<UCameraShakeBase> HitImpactShakeClass;

	FTimerHandle DelayHandle;
	float OwnerSavedTimeDilation;
	bool bIsHitPause = false;

	TWeakObjectPtr<AActor> OwnerActorWeakPtr;
	TWeakObjectPtr<AActor> TargetActorWeakPtr;
	TArray<TWeakObjectPtr<AActor>>AffectedTargets;

	FName HitPause_Name;
};
