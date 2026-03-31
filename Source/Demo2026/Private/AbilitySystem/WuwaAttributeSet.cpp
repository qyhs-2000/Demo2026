// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/WuwaAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffectTypes.h"
#include "WuwaBlueprintFunctionLibrary.h"
#include "WarriorGameplayTags.h"
#include "Character/WuwaBaseCharater.h"
#include "Components/UI/PawnUIComponent.h"
#include "Interfaces/PawnUIInterface.h"
#include "Net/UnrealNetwork.h"
#include "AbilitySystem/WuwaAbilitySystemComponent.h"
#include "DebugHelper.h"

UWuwaAttributeSet::UWuwaAttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitAttackPower(1.f);
	InitDefensePower(1.f);
	InitDamageTaken(0.f);
}

void UWuwaAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	//const bool bIsServer = Data.Target.AbilitySystemComponent()
	if (!CachedPawnUIInterface.IsValid())
	{
		CachedPawnUIInterface = Cast<IPawnUIInterface>(Data.Target.GetAvatarActor());
	}
	checkf(CachedPawnUIInterface.IsValid(), TEXT("%s didn't implement IPawnUIInterface"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());
	UPawnUIComponent* PawnUIComponent = CachedPawnUIInterface->GetPawnUIComponent();
	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);
		//PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
	}

	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetCurrentHealth();
		const float NewHealth = FMath::Clamp(OldHealth - GetDamageTaken(), 0.f, GetMaxHealth());
		SetCurrentHealth(NewHealth);
		if (AWuwaBaseCharacter* BaseCharacter = Cast<AWuwaBaseCharacter>(GetOwningActor()))
		{
			if (PawnUIComponent)
			{
				float NewHealthPercent = (float)NewHealth / GetMaxHealth();
				PawnUIComponent->OnCurrentHealthChanged.Broadcast(NewHealthPercent);
			}
		}
		//debug::Print(FString::Printf(TEXT("%s ,Current Health: %f"),*GetOwningActor()->GetActorNameOrLabel(), NewHealth));

		if (NewHealth <= 0.f)
		{
			UWuwaBlueprintFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), WuwaGameplayTags::Shared_Status_Death);
		}
	}
}

void UWuwaAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UWuwaAttributeSet, CurrentHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWuwaAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	/*DOREPLIFETIME_CONDITION_NOTIFY(UWuwaAttributeSet, AttackPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWuwaAttributeSet, DefensePower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWuwaAttributeSet, DamageTaken, COND_None, REPNOTIFY_Always);*/

}

void UWuwaAttributeSet::OnRep_CurrentHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWuwaAttributeSet, CurrentHealth, OldValue);
}

void UWuwaAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWuwaAttributeSet, MaxHealth, OldValue);
}
