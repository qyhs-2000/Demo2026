// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/WuwaGameplayAbility.h"

#include "WuwaEnemyGameplayAbility.generated.h"

/**
 * 
 */

class AWuwaEnemyCharacter;

UCLASS()
class DEMO2026_API UWuwaEnemyGameplayAbility : public UWuwaGameplayAbility
{
	GENERATED_BODY()
public:
	AWuwaEnemyCharacter* GetEnemyCharacterFromActorInfo();
	FGameplayEffectSpecHandle MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat);
private:
	TWeakObjectPtr<AWuwaEnemyCharacter> CachedEnemyCharacter;
};
