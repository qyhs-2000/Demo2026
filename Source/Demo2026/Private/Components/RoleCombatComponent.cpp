// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/RoleCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "WarriorGameplayTags.h"
void URoleCombatComponent::RegisterSpawnedWeapon(AWuwaWeaponBase * SpawnedWeapon)
{
	Super::RegisterSpawnedWeapon(SpawnedWeapon);
}

void URoleCombatComponent::OnWeaponHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor))
	{
		return;
	}

	Super::OnWeaponHitTargetActor(HitActor);
	FGameplayEventData Data;
	Data.Target = HitActor;
	Data.Instigator = GetOwningPawn();

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
	GetOwningPawn(),
	WuwaGameplayTags::Shared_Event_MeleeHit,
	Data
	);

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		WuwaGameplayTags::Player_Event_HitPause,
		Data
	);
}
