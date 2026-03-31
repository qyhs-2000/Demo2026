// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UI/PawnUIComponent.h"

#include "AbilitySystem/WuwaAttributeSet.h"
void UPawnUIComponent::InitializeComp(UWuwaAbilitySystemComponent* InAsc)
{
	if (!InAsc)
	{
		return;
	}
	AbilitySystemComponent = InAsc;
	AttributeSet = AbilitySystemComponent->GetSet<UWuwaAttributeSet>();
	check(AttributeSet);
	BindCallback();
}



void UPawnUIComponent::HandleCurrentHealthChanged(const FOnAttributeChangeData& ChangeData)
{
	if (!AttributeSet)
	{
		return;
	}
	const float MaxHealth = AttributeSet->GetMaxHealth();
	const float CurrentHealth = AttributeSet->GetCurrentHealth();

	const float HealthPercent = MaxHealth > 0.f ? ChangeData.NewValue / MaxHealth : 0.f;
	OnCurrentHealthChanged.Broadcast(HealthPercent);
}

void UPawnUIComponent::BindCallback()
{
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UWuwaAttributeSet::GetCurrentHealthAttribute()).AddUObject(this, &ThisClass::HandleCurrentHealthChanged);
	//AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UWuwaAttributeSet::GetMaxHealthAttribute()).AddUObject(this, &ThisClass::HandleMaxHealthChanged);
}

float UPawnUIComponent::GetCurrentHealthPercent() const
{
	if (AttributeSet)
	{
		float MaxHealth = AttributeSet->GetMaxHealth();
		return (MaxHealth > 0.f) ? (AttributeSet->GetCurrentHealth() / MaxHealth) : 0.f;
	}
	return 0.0f;
}
