// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/WuwaGameplayAbility.h"
#include "WuwaRoleGameplayAbility.generated.h"

/**
 * 
 */

class AWuwaPlayerCharater;

UCLASS()
class DEMO2026_API UWuwaRoleGameplayAbility : public UWuwaGameplayAbility
{
	GENERATED_BODY()
	
public:
	AWuwaPlayerCharater* GetRoleCharacterInfo();
private:
	TWeakObjectPtr<AWuwaPlayerCharater> CachedRoleCharacterInfo;
};
