// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/EnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "WuwaBlueprintFunctionLibrary.h"
#include "WarriorGameplayTags.h"

void UEnemyCombatComponent::OnWeaponHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor))
	{
		return;
	}

	Super::OnWeaponHitTargetActor(HitActor);
	FGameplayEventData Data;
	Data.Target = HitActor;
	Data.Instigator = GetOwningPawn();
	if (UWuwaBlueprintFunctionLibrary::NativeDoesActorHaveTag(HitActor, WuwaGameplayTags::Player_Status_Dodging))
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			HitActor,
			WuwaGameplayTags::Player_Event_OnPerfectDodgeTrigger,
			Data
		);
	}
	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			GetOwningPawn(),
			WuwaGameplayTags::Shared_Event_MeleeHit,
			Data
		);

	}
}
