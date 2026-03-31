// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "WuwaBlueprintFunctionLibrary.generated.h"

/**
 * 
 */

class UWuwaAbilitySystemComponent;

UCLASS()
class DEMO2026_API UWuwaBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static bool IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn);
	static UWuwaAbilitySystemComponent* GetASCFromActorInfo(AActor * InActor);
	static void AddGameplayTagToActorIfNone(AActor* TargetActor, FGameplayTag TagToAdd);
	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag Tag);
};
