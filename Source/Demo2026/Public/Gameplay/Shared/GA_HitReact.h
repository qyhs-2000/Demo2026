// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Enemy/WuwaEnemyGameplayAbility.h"
#include "GA_HitReact.generated.h"

/**
 * 
 */
UCLASS()
class DEMO2026_API UGA_HitReact : public UWuwaEnemyGameplayAbility
{
	GENERATED_BODY()

public:
	UGA_HitReact();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual UAnimMontage* GetHitReactMontage();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Montage")
	TArray<UAnimMontage*> HitReactMontages;
};
