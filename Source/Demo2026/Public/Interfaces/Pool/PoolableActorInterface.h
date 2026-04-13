// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PoolableActorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPoolableActorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DEMO2026_API IPoolableActorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PoolableActor")
	void OnAcquireFromPool();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PoolableActor")
	void OnReleaseToPool();
};
