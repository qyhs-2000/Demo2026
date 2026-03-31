// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Enemy/WuwaEnemyGameplayAbility.h"
#include "WuwaRoleGameplayAbility.generated.h"

/**
 * 
 */

class AWuwaPlayerCharater;
class AWuwaPlayerController;
UCLASS()
class DEMO2026_API UWuwaRoleGameplayAbility : public UWuwaGameplayAbility
{
	GENERATED_BODY()
	
public:
	AWuwaPlayerCharater* GetRoleCharacterInfo();
	FGameplayEffectSpecHandle MakeRoleDamageSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InBaseDamage);
	AWuwaPlayerController* GetRoleControllerFromActorInfo();
private:
	TWeakObjectPtr<AWuwaPlayerCharater> CachedRoleCharacterInfo;
};
