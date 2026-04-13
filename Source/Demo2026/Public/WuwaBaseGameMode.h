// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WuwaBaseGameMode.generated.h"

class AActor;

/**
 * 
 */
USTRUCT(BlueprintType)
struct DEMO2026_API FPoolPrewarmEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Object Pool")
	TSubclassOf<AActor> ActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Object Pool", meta = (ClampMin = "0"))
	int32 Count = 0;
};

UCLASS()
class DEMO2026_API AWuwaBaseGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Object Pool")
	TArray<FPoolPrewarmEntry> PrewarmPools;
};
