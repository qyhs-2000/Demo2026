// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "WuwaAIController.generated.h"

/**
 * 
 */

class UAISenseConfig_Sight;

UCLASS()
class DEMO2026_API AWuwaAIController : public AAIController
{
	GENERATED_BODY()
public:
	AWuwaAIController();
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UAISenseConfig_Sight* AISenseConfig_Sight;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	UAIPerceptionComponent* EnemyPerceptionComponent;

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	FName BBKeyName_TargetActor;
	UFUNCTION()
	void OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	//change team attribute
	ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
};
