// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Pool/PoolableActorInterface.h"
#include "WuwaProjectileBase.generated.h"

UCLASS()
class DEMO2026_API AWuwaProjectileBase : public AActor, public IPoolableActorInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWuwaProjectileBase();
	void FireInDirection(const FVector& ShootDirection);
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile", meta = (ClampMin = "0.0"))
	float PooledLifeSeconds = 4.f;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	class UBoxComponent* ProjectileCollisionBox;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	class UNiagaraComponent* ProjectileNiagaraComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void OnAcquireFromPool_Implementation() override;
	virtual void OnReleaseToPool_Implementation() override;

	
	void ReturnToPool();

private:
	FTimerHandle LifeTimeHandle;
};
