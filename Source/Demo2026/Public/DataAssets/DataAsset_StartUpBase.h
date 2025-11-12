// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpBase.generated.h"

/**
 * 
 */

class UWuwaAbilitySystemComponent;

UCLASS()
class DEMO2026_API UDataAsset_StartUpBase : public UDataAsset
{
	GENERATED_BODY()
	
public:
	virtual void GiveAbilityToAbilitSystemComponent(UWuwaAbilitySystemComponent* AbilitySystem,int32 ApplyLevel = 1);
};
