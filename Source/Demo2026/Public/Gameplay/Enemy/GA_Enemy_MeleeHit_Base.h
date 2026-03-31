// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Enemy/WuwaEnemyGameplayAbility.h"
#include "GA_Enemy_MeleeHit_Base.generated.h"

/**
 * 
 */
UCLASS()
class DEMO2026_API UGA_Enemy_MeleeHit_Base : public UWuwaEnemyGameplayAbility
{
	GENERATED_BODY()
public:
	UAnimMontage* GetRandomMontageToPlay();
	UGA_Enemy_MeleeHit_Base();
	virtual void OnAbilityActivate() override;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Montage")
	TArray<UAnimMontage*> MontagesToPlay;

	UFUNCTION()
	void HandleAttackDamage(FGameplayEventData Payload);

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> GE_DealDamage_Class;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	FScalableFloat BaseDamageScalableFloat;
};
