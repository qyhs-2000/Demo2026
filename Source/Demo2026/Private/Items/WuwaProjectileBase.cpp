// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/WuwaProjectileBase.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Subsystem/ObjectPoolSubsystem.h"
#include "DebugHelper.h"

// Sets default values
AWuwaProjectileBase::AWuwaProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ProjectileCollisionBox"));
	SetRootComponent(ProjectileCollisionBox);
	ProjectileCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	ProjectileCollisionBox->OnComponentHit.AddUniqueDynamic(this, &ThisClass::OnProjectileHit);

	ProjectileNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ProjectileNiagaraComponent"));
	ProjectileNiagaraComponent->SetupAttachment(GetRootComponent());
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 600.f;
	ProjectileMovementComponent->MaxSpeed = 800.f;
	ProjectileMovementComponent->Velocity = FVector(1.f, 0, 0);
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;

}

void AWuwaProjectileBase::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	debug::Print(FString::Printf(TEXT("Projectile Hit: %s"), *OtherActor->GetName()));
	ReturnToPool();
	//Destroy();
}

void AWuwaProjectileBase::OnAcquireFromPool_Implementation()
{
	GetWorld()->GetTimerManager().ClearTimer(LifeTimeHandle);

	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);

	ProjectileCollisionBox->Activate(true);
	ProjectileCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ProjectileMovementComponent->StopMovementImmediately();
}

void AWuwaProjectileBase::OnReleaseToPool_Implementation()
{
	GetWorld()->GetTimerManager().ClearTimer(LifeTimeHandle);

	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);

	ProjectileCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ProjectileCollisionBox->Deactivate();
	ProjectileMovementComponent->StopMovementImmediately();
	ProjectileMovementComponent->Deactivate();
}

void AWuwaProjectileBase::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection.GetSafeNormal() * ProjectileMovementComponent->InitialSpeed;
	ProjectileMovementComponent->Activate();

	GetWorld()->GetTimerManager().SetTimer(LifeTimeHandle, this, &ThisClass::ReturnToPool, PooledLifeSeconds, false);
}

void AWuwaProjectileBase::ReturnToPool()
{
	if (UObjectPoolSubsystem* Pool = GetWorld()->GetSubsystem<UObjectPoolSubsystem>())
    {
        Pool->ReleaseActor(this);
    }
}
