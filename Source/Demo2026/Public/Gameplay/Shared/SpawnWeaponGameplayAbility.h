// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/WuwaGameplayAbility.h"

#include "SpawnWeaponGameplayAbility.generated.h"

/**
 * 
 */

class AWuwaWeaponBase;

UCLASS()
class DEMO2026_API USpawnWeaponGameplayAbility : public UWuwaGameplayAbility
{
	GENERATED_BODY()
public:
	USpawnWeaponGameplayAbility();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AWuwaWeaponBase> WeaponClassToSpawn;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly,Replicated, Category = "Weapon")
	FName AttachedSocketName;


	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const override;
private:
	// 服务器生成武器（RPC）
	UFUNCTION(Server, Reliable)
	void ServerSpawnWeapon(const FGameplayAbilitySpecHandle& Handle, 
		const FGameplayAbilityActorInfo& ActorInfo,
		const FGameplayAbilityActivationInfo& ActivationInfo);

	// 实际生成逻辑（只在服务器执行）
	void SpawnWeaponInternal(const FGameplayAbilitySpecHandle& Handle,
		const FGameplayAbilityActorInfo& ActorInfo,
		const FGameplayAbilityActivationInfo& ActivationInfo);
	
};
