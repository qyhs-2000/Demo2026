// Fill out your copyright notice in the Description page of Project Settings.


#include "WuwaBaseGameMode.h"
#include "Subsystem/ObjectPoolSubsystem.h"


void AWuwaBaseGameMode::BeginPlay()
{
    Super::BeginPlay();
    if(UObjectPoolSubsystem* PoolSubsystem = GetWorld()->GetSubsystem<UObjectPoolSubsystem>())
    {
        for (const FPoolPrewarmEntry& Entry : PrewarmPools)
        {
            if (!Entry.ActorClass || Entry.Count <= 0)
            {
                continue;
            }

            PoolSubsystem->PreWarmPool(Entry.ActorClass, Entry.Count);
        }
    }
}
