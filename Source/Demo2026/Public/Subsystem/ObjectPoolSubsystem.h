// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ObjectPoolSubsystem.generated.h"

/**
 * 
 */

struct FActorPool
{
	UPROPERTY()
	TArray<AActor*> AvailableActors;

	UPROPERTY()
	TArray<AActor*> InUseActors;
};

UCLASS()
class DEMO2026_API UObjectPoolSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	AActor * AcquireActor(TSubclassOf<AActor> ActorClass,const FTransform & SpawnTransform);
	void ReleaseActor(AActor * ActorToRelease);
	AActor * CreatePooledActor(TSubclassOf<AActor> ActorClass);

	void PreWarmPool(TSubclassOf<AActor> ActorClass, int32 NumToPrewarm);
private:
	TMap<TSubclassOf<AActor>, FActorPool> ObjectPools;
};
