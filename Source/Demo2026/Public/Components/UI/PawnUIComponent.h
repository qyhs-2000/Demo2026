// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponent.h"
#include "AbilitySystem/WuwaAbilitySystemComponent.h"
//#include "AbilitySystemComponent.h"
#include "PawnUIComponent.generated.h"

/**
 * 
 */
class UWuwaAttributeSet;
//struct FOnAttributeChangeData;
class UWuwaAbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCurrentHealthChanged, float, NewPercent);

UCLASS()
class DEMO2026_API UPawnUIComponent : public UPawnExtensionComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnCurrentHealthChanged OnCurrentHealthChanged;
	void InitializeComp(UWuwaAbilitySystemComponent* InAsc);

	void HandleCurrentHealthChanged(const FOnAttributeChangeData& ChangeData);


	//void HandleMaxHealthChanged(const FOnAttributeChangeData& ChangeData);
protected:
	void BindCallback();
private:
	UPROPERTY()
	TObjectPtr<UWuwaAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<const UWuwaAttributeSet> AttributeSet;

	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetCurrentHealthPercent()const;

	bool bIsInitialized = false;
};
