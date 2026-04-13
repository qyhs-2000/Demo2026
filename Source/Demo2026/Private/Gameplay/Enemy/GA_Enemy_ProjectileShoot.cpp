// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Enemy/GA_Enemy_ProjectileShoot.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Subsystem/ObjectPoolSubsystem.h"
#include "Items/WuwaProjectileBase.h"

UGA_Enemy_ProjectileShoot::UGA_Enemy_ProjectileShoot()
{
    AbilityTags.AddTag(WuwaGameplayTags::Enemy_Ability_Ranged);
}

void UGA_Enemy_ProjectileShoot::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    if(ShootMontage)
    {
        UAbilityTask_PlayMontageAndWait* Task = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, ShootMontage, 1.0f);
        Task->OnBlendOut.AddUniqueDynamic(this, &UGA_Enemy_ProjectileShoot::OnMontageCancelOrComplete);
        Task->OnCompleted.AddUniqueDynamic(this, &UGA_Enemy_ProjectileShoot::OnMontageCancelOrComplete);
        Task->OnCancelled.AddUniqueDynamic(this, &UGA_Enemy_ProjectileShoot::OnMontageCancelOrComplete);
        Task->ReadyForActivation();


        UAbilityTask_WaitGameplayEvent* WaitEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, WuwaGameplayTags::Enemy_Event_ProjectileShoot);
        WaitEventTask->EventReceived.AddUniqueDynamic(this, &UGA_Enemy_ProjectileShoot::SpawnProjectile);
        WaitEventTask->ReadyForActivation();
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("ShootMontage is not set in %s"), *GetName());
    }
   
    //SpawnProjectile(FGameplayEventData()); // Optionally spawn a projectile immediately without waiting for the montage event. You can remove this if you only want to spawn on the event.
    //EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void UGA_Enemy_ProjectileShoot::SpawnProjectile(FGameplayEventData Payload)
{
    // Here you would spawn your projectile actor and set its initial trajectory based on the enemy's facing direction or target location.
    UE_LOG(LogTemp, Log, TEXT("Spawning projectile for %s"), *GetName());
    if(ProjectileClass)
    {
        AActor* AvatarActor = GetAvatarActorFromActorInfo();
        if(AvatarActor)
        {


            FVector SpawnLocation = AvatarActor->GetActorLocation() + AvatarActor->GetActorForwardVector() * 100.0f; // Spawn in front of the enemy
            FRotator SpawnRotation = AvatarActor->GetActorRotation();

            UObjectPoolSubsystem* PoolSubsystem = GetWorld()->GetSubsystem<UObjectPoolSubsystem>();
            if(PoolSubsystem)
            {
                AWuwaProjectileBase* Projectile = Cast<AWuwaProjectileBase>(PoolSubsystem->AcquireActor(ProjectileClass, FTransform(SpawnRotation, SpawnLocation)));
                if(Projectile)
                {
                    UE_LOG(LogTemp, Log, TEXT("Acquired projectile from pool for %s"), *GetName());
                    Projectile->FireInDirection(AvatarActor->GetActorForwardVector());
                }
                else
                {
                    UE_LOG(LogTemp, Warning, TEXT("Failed to acquire projectile from pool for %s"), *GetName());
                }
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("ObjectPoolSubsystem not found for %s"), *GetName());
            }
            //GetWorld()->SpawnActor<AWuwaProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation)->FireInDirection(AvatarActor->GetActorForwardVector());
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("ProjectileClass is not set in %s"), *GetName());
    }
}
