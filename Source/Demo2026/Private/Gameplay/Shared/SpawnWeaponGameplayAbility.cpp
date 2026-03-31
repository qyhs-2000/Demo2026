// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Shared/SpawnWeaponGameplayAbility.h"
#include "Weapon/WuwaWeaponBase.h"
#include "Components/PawnCombatComponent.h"
#include "Net/UnrealNetwork.h"
#include "Character/WuwaBaseCharater.h"

USpawnWeaponGameplayAbility::USpawnWeaponGameplayAbility()
{
	AbilityTags.AddTag(WuwaGameplayTags::Shared_Ability_SpawnWeapon);
}

void USpawnWeaponGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);


	if (!HasAuthority(&ActivationInfo))
	{
		ServerSpawnWeapon(Handle, *ActorInfo, ActivationInfo);
		return;
	}

	SpawnWeaponInternal(Handle, *ActorInfo, ActivationInfo);

}

void USpawnWeaponGameplayAbility::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(USpawnWeaponGameplayAbility, AttachedSocketName);
}

void USpawnWeaponGameplayAbility::ServerSpawnWeapon_Implementation(
    const FGameplayAbilitySpecHandle& Handle,
    const FGameplayAbilityActorInfo& ActorInfo,
    const FGameplayAbilityActivationInfo& ActivationInfo)
{

    SpawnWeaponInternal(Handle, ActorInfo, ActivationInfo);
}

void USpawnWeaponGameplayAbility::SpawnWeaponInternal(
    const FGameplayAbilitySpecHandle& Handle,
    const FGameplayAbilityActorInfo& ActorInfo,
    const FGameplayAbilityActivationInfo& ActivationInfo)
{
    if (!HasAuthority(&ActivationInfo))
    {
        return;
    }

    UWorld* World = GetWorld();
    AWuwaBaseCharacter* Character = Cast<AWuwaBaseCharacter>(ActorInfo.AvatarActor.Get());
    if (!World || !Character)
    {
        EndAbility(Handle, &ActorInfo, ActivationInfo, true, false);
        return;
    }

    FActorSpawnParameters SpawnParameters;
    SpawnParameters.Owner = Character;
    SpawnParameters.Instigator = Character;
    SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    USkeletalMeshComponent* Mesh = Character->GetMesh();
    if (!Mesh)
    {
        EndAbility(Handle, &ActorInfo, ActivationInfo, true, false);
        return;
    }

    FTransform SocketTransform = Mesh->GetSocketTransform(AttachedSocketName);

    AWuwaWeaponBase* SpawnedWeapon = World->SpawnActorDeferred<AWuwaWeaponBase>(
        WeaponClassToSpawn,
        SocketTransform,
        Character,
        Character,
        ESpawnActorCollisionHandlingMethod::AlwaysSpawn
    );

    if (SpawnedWeapon)
    {
        SpawnedWeapon->FinishSpawning(SocketTransform);

        SpawnedWeapon->SetReplicates(true);
        SpawnedWeapon->SetReplicateMovement(true);

        SpawnedWeapon->AttachToComponent(Mesh, 
            FAttachmentTransformRules::SnapToTargetNotIncludingScale, 
            AttachedSocketName);

        if (UPawnCombatComponent* CombatComp = Character->GetPawnCombatComponent())
        {
            CombatComp->RegisterSpawnedWeapon(SpawnedWeapon);
        }

        UE_LOG(LogTemp, Log, TEXT("[Server] Spawned weapon: %s for character: %s"), 
            *SpawnedWeapon->GetName(), *Character->GetName());
    }

    EndAbility(Handle, &ActorInfo, ActivationInfo, true, false);
}
