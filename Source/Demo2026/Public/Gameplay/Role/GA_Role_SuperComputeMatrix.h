// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/WuwaRoleGameplayAbility.h"
#include "GA_Role_SuperComputeMatrix.generated.h"

/**
 * 
 */
UCLASS()
class DEMO2026_API UGA_Role_SuperComputeMatrix : public UWuwaRoleGameplayAbility
{
	GENERATED_BODY()
public:
	UGA_Role_SuperComputeMatrix();
	virtual void OnAbilityActivate() override;
	virtual void OnEndAbility() override;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> CooldownGE;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Time Freeze")
	float WorldFreezeDilation = 0.05f;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Time Freeze")
	float ActivateDuration = 3.f;
	UFUNCTION()
	void RestoreTimeAndEnd();

	FName TimeEffectName;
private:
	FTimerHandle FreezeTimeHandle;
	float SavedWorldDilation = 1.f;
	float SavedPlayerDilation = 1.f;
};
