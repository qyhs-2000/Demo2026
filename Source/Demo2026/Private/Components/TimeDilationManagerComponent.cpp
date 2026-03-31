// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TimeDilationManagerComponent.h"
#include "Kismet/GameplayStatics.h"

UTimeDilationManagerComponent::UTimeDilationManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTimeDilationManagerComponent::AddTimeOverride(FName SourceID, float TargetScale, int32 Priority,bool bIsAbsolute)
{
	if (!SourceID.IsNone())
	{
		ActiveEffects.Add(SourceID, FTimeDilationOverride(TargetScale, Priority, bIsAbsolute));
		EvaluateTimeDilation();
	}
}

void UTimeDilationManagerComponent::RemoveTimeOverride(FName SourceID)
{
	if (!SourceID.IsNone() &&ActiveEffects.Contains(SourceID))
	{
		ActiveEffects.Remove(SourceID);
		EvaluateTimeDilation();
	}

}

void UTimeDilationManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	ActiveEffects.Empty();
}

void UTimeDilationManagerComponent::EvaluateTimeDilation()
{
	AActor* Owner = GetOwner();
	if (!Owner)
	{
		return;
	}

	if (ActiveEffects.Num() == 0)
	{
		Owner->CustomTimeDilation = 1.f;
		return;
	}

	int32 HighestPriority = -1.f;
	FTimeDilationOverride BestTimeOverride;
	for (const auto& Pair : ActiveEffects)
	{
		if (Pair.Value.Priority > HighestPriority)
		{
			HighestPriority = Pair.Value.Priority;
			BestTimeOverride = Pair.Value;
		}
	}
	float FinalTimeScale = BestTimeOverride.TimeScale;
	if (BestTimeOverride.bIsAbsolute)
	{
		float CurrentGlobal = UGameplayStatics::GetGlobalTimeDilation(this);
		CurrentGlobal = FMath::Max(CurrentGlobal, 0.001f); 
		FinalTimeScale = BestTimeOverride.TimeScale / CurrentGlobal;
	}

	Owner->CustomTimeDilation = FinalTimeScale;
}
