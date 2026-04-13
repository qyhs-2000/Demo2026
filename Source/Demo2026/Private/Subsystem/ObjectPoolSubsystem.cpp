// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/ObjectPoolSubsystem.h"
#include "Interfaces/Pool/PoolableActorInterface.h"

void UObjectPoolSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

}

void UObjectPoolSubsystem::Deinitialize()
{
    for(auto& PoolPair : ObjectPools)
    {
        for(AActor* Actor : PoolPair.Value.AvailableActors)
        {
            if(IsValid(Actor))
            {
                Actor->Destroy();
            }
        }
        for(AActor* Actor : PoolPair.Value.InUseActors)
        {
            if(IsValid(Actor))
            {
                Actor->Destroy();
            }
        }
    }    
    ObjectPools.Empty();
    Super::Deinitialize();
    UE_LOG(LogTemp, Log, TEXT("ObjectPoolSubsystem Deinitialized"));
}

AActor * UObjectPoolSubsystem::CreatePooledActor(TSubclassOf<AActor> ActorClass)
{
    if(!GetWorld() ||!ActorClass)
    {
        return nullptr;
    }
    AActor * NewActor = GetWorld()->SpawnActor<AActor>(ActorClass, FTransform::Identity);
    if(NewActor)
    {
        NewActor->SetActorEnableCollision(false);
        NewActor->SetActorHiddenInGame(true);
        NewActor->SetActorTickEnabled(false);
    }
    return NewActor;
}

AActor * UObjectPoolSubsystem::AcquireActor(TSubclassOf<AActor> ActorClass,const FTransform & SpawnTransform)
{
    if(!ActorClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("AcquireActor called with null ActorClass"));
        return nullptr;
    }
    FActorPool & Pool = ObjectPools.FindOrAdd(ActorClass);
    AActor * Actor = nullptr;

    while (Pool.AvailableActors.Num() > 0 && !IsValid(Actor))
    {
        Actor = Pool.AvailableActors.Pop();
    }

    if(!IsValid(Actor))
    {
        Actor = CreatePooledActor(ActorClass);
    }
    if(!IsValid(Actor))
    {
        return nullptr;
    }
    Pool.InUseActors.Add(Actor);
    Actor->SetActorTransform(SpawnTransform);
    Actor->SetActorEnableCollision(true);
    Actor->SetActorHiddenInGame(false);
    Actor->SetActorTickEnabled(true);

    if(Actor->GetClass()->ImplementsInterface(UPoolableActorInterface::StaticClass()))
    {
        IPoolableActorInterface::Execute_OnAcquireFromPool(Actor);
    }
    return Actor;
}

void UObjectPoolSubsystem::ReleaseActor(AActor * ActorToRelease)
{
    if(!IsValid(ActorToRelease))
    {
        return;
    }
    TSubclassOf<AActor> ActorClass = ActorToRelease->GetClass();
    FActorPool * Pool = ObjectPools.Find(ActorClass);
    if(!Pool)
    {
        UE_LOG(LogTemp, Warning, TEXT("Trying to release an actor of class %s that is not managed by the pool"), *ActorClass->GetName());
        return;
    }

    Pool->InUseActors.Remove(ActorToRelease);
    Pool->AvailableActors.Remove(ActorToRelease);

    if(ActorToRelease->GetClass()->ImplementsInterface(UPoolableActorInterface::StaticClass()))
    {
        IPoolableActorInterface::Execute_OnReleaseToPool(ActorToRelease);
    }
    ActorToRelease->SetActorEnableCollision(false);
    ActorToRelease->SetActorHiddenInGame(true);
    ActorToRelease->SetActorTickEnabled(false);
    Pool->AvailableActors.Add(ActorToRelease);
}

void UObjectPoolSubsystem::PreWarmPool(TSubclassOf<AActor> ActorClass, int32 NumToPrewarm)
{
    if(!ActorClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("PrewarmPool called with null ActorClass"));
        return;
    }
    FActorPool & Pool = ObjectPools.FindOrAdd(ActorClass);
    for(int32 i=0;i<NumToPrewarm;++i)
    {
        AActor * NewActor = CreatePooledActor(ActorClass);
        if(IsValid(NewActor))
        {
            Pool.AvailableActors.Add(NewActor);
        }
    }
}
