// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UI/PawnUIComponent.h"

#include "AbilitySystem/WuwaAttributeSet.h"
void UPawnUIComponent::InitializeComp(UWuwaAbilitySystemComponent* InAsc)
{
	if (!InAsc|| bIsInitialized)
	{
		return;
	}
	AbilitySystemComponent = InAsc;
	AttributeSet = AbilitySystemComponent->GetSet<UWuwaAttributeSet>();
	check(AttributeSet);
	if(AttributeSet)
	BindCallback();
	bIsInitialized = true;
}



void UPawnUIComponent::HandleCurrentHealthChanged(const FOnAttributeChangeData& ChangeData)
{
	if (!AttributeSet||!bIsInitialized)
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
	if (!AbilitySystemComponent) return;
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UWuwaAttributeSet::GetCurrentHealthAttribute()).AddUObject(this, &ThisClass::HandleCurrentHealthChanged);
	//AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UWuwaAttributeSet::GetMaxHealthAttribute()).AddUObject(this, &ThisClass::HandleMaxHealthChanged);
}

float UPawnUIComponent::GetCurrentHealthPercent() const
{
	if (!bIsInitialized ||!AttributeSet)
	{
		return 0.0f;
	}
	float MaxHealth = AttributeSet->GetMaxHealth();
		return (MaxHealth > 0.f) ? (AttributeSet->GetCurrentHealth() / MaxHealth) : 0.f;
}
