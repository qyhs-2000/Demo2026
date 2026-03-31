// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponent.h"
#include "Data/EnumTypes.h"
#include "PawnCombatComponent.generated.h"

/**
 *
 */

class AWuwaWeaponBase;
UCLASS()
class DEMO2026_API UPawnCombatComponent : public UPawnExtensionComponent
{
	GENERATED_BODY()
public:
	virtual void RegisterSpawnedWeapon(AWuwaWeaponBase* SpawnedWeapon);
	virtual void OnWeaponHitTargetActor(AActor* HitActor);
	virtual void OnWeaponPullFormTargetActor(AActor* HitActor);
	virtual void WeaponHitActorByWeaponType(EWeaponType WeaponType, AActor* HitActor);
	void ToggleWeaponCollision(EWeaponType WeaponType, ECollisionEnabled::Type CollisionType);
	inline TArray<AWuwaWeaponBase*> GetSpawnedWeapons() {
		return SpawnedWeapons;
	};
	AWuwaWeaponBase* GetWeaponByWeaponType(EWeaponType WeaponType);
protected:
	TArray<AActor*> OverlappedActors;
	TArray<AActor*> HitActors;
private:
	TArray<AWuwaWeaponBase*> SpawnedWeapons;
};
