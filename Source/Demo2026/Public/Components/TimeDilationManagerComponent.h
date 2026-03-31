// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponent.h"
#include "TimeDilationManagerComponent.generated.h"

/**
 * 
 */
UCLASS()
class DEMO2026_API UTimeDilationManagerComponent : public UPawnExtensionComponent
{
	GENERATED_BODY()
public:
	UTimeDilationManagerComponent();
	void AddTimeOverride(FName SourceID, float TargetScale, int32 Priority,bool bIsAbsolute);
	void RemoveTimeOverride(FName SouceID);
	virtual void BeginPlay() override;
private:
	struct FTimeDilationOverride
	{
		float TimeScale;
		int32 Priority;
		bool bIsAbsolute;    //如果为true，表示TimeScale是最终速度，不受global影响
		FTimeDilationOverride() :Priority(0), TimeScale(1.f), bIsAbsolute(false) {};
		FTimeDilationOverride(float InScale, float InPriority, bool isAbsolute = false) :TimeScale(InScale), Priority(InPriority), bIsAbsolute(isAbsolute) {}
	};
	TMap<FName, FTimeDilationOverride> ActiveEffects;

	void EvaluateTimeDilation();
};
