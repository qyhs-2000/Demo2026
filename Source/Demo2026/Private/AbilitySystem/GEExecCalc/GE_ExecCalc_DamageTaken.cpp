// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GEExecCalc/GE_ExecCalc_DamageTaken.h"
#include "WarriorGameplayTags.h"
//void UGE_ExecCalc_DamageTaken::Execute(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
//{
//}

void UGE_ExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();
	float BaseDamage = 0.f;
	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(WuwaGameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
		}
	}
	float FinalDamage = BaseDamage;
	
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetWuwaDamageCapture().DamageTakenProperty, EGameplayModOp::Override,
		FinalDamage));
}
