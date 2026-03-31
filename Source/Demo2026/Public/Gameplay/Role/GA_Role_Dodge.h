// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/WuwaRoleGameplayAbility.h"
#include "GA_Role_Dodge.generated.h"

/**
 * 
 */

class UAbilityTask_PlayMontageAndWait;

UCLASS()
class DEMO2026_API UGA_Role_Dodge : public UWuwaRoleGameplayAbility
{
	GENERATED_BODY()
public:
	UGA_Role_Dodge();
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "AnimMontage")
	UAnimMontage* AM_MoveForward;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "AnimMontage")
	UAnimMontage* AM_MoveBack;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "AnimMontage")
	UAnimMontage* AM_DodgeForward;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "AnimMontage")
	UAnimMontage* AM_DodgeBack;

	virtual void OnAbilityActivate() override;

	UFUNCTION()
	void OnPerfectDodgeTrigger(FGameplayEventData Payload);

	void CancelDodge();
	UAbilityTask_PlayMontageAndWait* CurrentPlayTask = nullptr;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UGameplayEffect* CooldownGE;
};
