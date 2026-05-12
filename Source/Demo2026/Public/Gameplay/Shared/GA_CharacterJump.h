// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/WuwaRoleGameplayAbility.h"
#include "GA_CharacterJump.generated.h"

/**
 * 
 */
UCLASS()
class DEMO2026_API UGA_CharacterJump : public UWuwaRoleGameplayAbility
{
	GENERATED_BODY()
public:
	UGA_CharacterJump();
	virtual void OnAbilityActivate() override;
private:

};
