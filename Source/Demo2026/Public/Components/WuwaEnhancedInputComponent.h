// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/DataAsset_InputConfig.h"
#include "WuwaEnhancedInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class DEMO2026_API UWuwaEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
public:
	template<typename UserObject,typename CallbackFunc>
	void BindNativeInputAction(const UDataAsset_InputConfig * InputConfigDataAsset,const FGameplayTag InTagToBind,ETriggerEvent TriggerEvent,UserObject * context_object,CallbackFunc callback);

	template<typename UserObject,typename CallbackFunc>
	void BindAbilityInputAction(const UDataAsset_InputConfig* InputConfigDataAsset,UserObject * context_object,CallbackFunc InputPressedCallback,CallbackFunc InputReleasedCallback);
};

template<typename UserObject,typename CallbackFunc>
void UWuwaEnhancedInputComponent::BindNativeInputAction(const UDataAsset_InputConfig* InputConfigDataAsset,const FGameplayTag InTagToBind,ETriggerEvent TriggerEvent,UserObject * context_object,CallbackFunc callback)
{
	if (UInputAction* InputAction = InputConfigDataAsset->FindNativeInputActionByTag(InTagToBind))
	{
		BindAction(InputAction, TriggerEvent, context_object, callback);
	}
}

template<typename UserObject, typename CallbackFunc>
inline void UWuwaEnhancedInputComponent::BindAbilityInputAction(const UDataAsset_InputConfig* InputConfigDataAsset,UserObject * context_object,CallbackFunc InputPressedCallback,CallbackFunc InputReleasedCallback)
{
	check(InputConfigDataAsset);
	for (const FWuwaInputActionConfig& InputConfig : InputConfigDataAsset->AbilityInputActions)
	{
		BindAction(InputConfig.InputAction, ETriggerEvent::Started, context_object, InputPressedCallback,InputConfig.InputTag);
		BindAction(InputConfig.InputAction, ETriggerEvent::Completed, context_object, InputReleasedCallback,InputConfig.InputTag);
	}

}
