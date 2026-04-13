// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Enemy/WuwaEnemyGameplayAbility.h"
#include "GA_Enemy_ProjectileShoot.generated.h"

/**
 * 
 */
UCLASS()
class DEMO2026_API UGA_Enemy_ProjectileShoot : public UWuwaEnemyGameplayAbility
{
	GENERATED_BODY()
public:
	UGA_Enemy_ProjectileShoot();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	UAnimMontage* ShootMontage;

	UFUNCTION()
	void SpawnProjectile( FGameplayEventData Payload);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	TSubclassOf<AActor> ProjectileClass;
};
