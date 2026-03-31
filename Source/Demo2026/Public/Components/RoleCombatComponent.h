// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnCombatComponent.h"
#include "RoleCombatComponent.generated.h"

/**
 * 
 */
UCLASS()
class DEMO2026_API URoleCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()
public:

protected:
	virtual void RegisterSpawnedWeapon(AWuwaWeaponBase * SpawnedWeapon) override;
	virtual void OnWeaponHitTargetActor(AActor* HitActor);
};
