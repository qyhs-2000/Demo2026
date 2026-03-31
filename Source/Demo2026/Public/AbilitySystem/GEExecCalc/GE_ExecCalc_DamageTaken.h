// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "AbilitySystem/WuwaAttributeSet.h"
#include "GE_ExecCalc_DamageTaken.generated.h"

/**
 *
 */
struct FWuwaDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)
	FWuwaDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWuwaAttributeSet, AttackPower, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWuwaAttributeSet, DefensePower, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWuwaAttributeSet, DamageTaken, Source, false);
	}
};

static const FWuwaDamageCapture& GetWuwaDamageCapture()
{
	static FWuwaDamageCapture WuwaDamageCapture;
	return WuwaDamageCapture;
}

UCLASS()
class DEMO2026_API UGE_ExecCalc_DamageTaken : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UGE_ExecCalc_DamageTaken()
	{
		RelevantAttributesToCapture.Add(GetWuwaDamageCapture().AttackPowerDef);
		RelevantAttributesToCapture.Add(GetWuwaDamageCapture().DefensePowerDef);
		RelevantAttributesToCapture.Add(GetWuwaDamageCapture().DamageTakenDef);

	}
	void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
