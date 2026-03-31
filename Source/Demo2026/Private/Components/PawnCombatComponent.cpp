// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PawnCombatComponent.h"
#include "Weapon/WuwaWeaponBase.h"
#include "DebugHelper.h"

void UPawnCombatComponent::RegisterSpawnedWeapon(AWuwaWeaponBase* SpawnedWeapon)
{
	SpawnedWeapons.AddUnique(SpawnedWeapon);
	SpawnedWeapon->OnWeaponHitTarget.BindUObject(this, &ThisClass::OnWeaponHitTargetActor);
	SpawnedWeapon->OnWeaponPullFromTarget.BindUObject(this, &ThisClass::OnWeaponPullFormTargetActor);
}

void UPawnCombatComponent::OnWeaponHitTargetActor(AActor* HitActor)
{
	debug::Print(FString::Printf(TEXT("Hit Actor % s"),*HitActor->GetActorNameOrLabel()));
}

void UPawnCombatComponent::OnWeaponPullFormTargetActor(AActor* HitActor)
{
	//debug::Print(TEXT("Pull From Actor"));
	//OverlappedActors.Empty();
}

void UPawnCombatComponent::WeaponHitActorByWeaponType(EWeaponType WeaponType, AActor* HitActor)
{
	for (AWuwaWeaponBase* Weapon : SpawnedWeapons)
	{
		if (Weapon->WeaponType == WeaponType)
		{
			Weapon->HitActor(HitActor);
			break;
		}
	}
}

void UPawnCombatComponent::ToggleWeaponCollision(EWeaponType WeaponType,ECollisionEnabled::Type CollisionType)
{
	for (AWuwaWeaponBase* Weapon : SpawnedWeapons)
	{
		if (Weapon->WeaponType == WeaponType)
		{
			Weapon->ToggleWeaponCollision(CollisionType);
			if (CollisionType == ECollisionEnabled::NoCollision)
			{
				OverlappedActors.Empty();
			}
			break;
		}
	}
}

AWuwaWeaponBase* UPawnCombatComponent::GetWeaponByWeaponType(EWeaponType WeaponType)
{
	for (AWuwaWeaponBase* Weapon : SpawnedWeapons)
	{
		if (Weapon->WeaponType == WeaponType)
		{
			return Weapon;
		}
	}
	return nullptr;
}
