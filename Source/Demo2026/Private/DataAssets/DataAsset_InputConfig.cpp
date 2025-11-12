// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/DataAsset_InputConfig.h"

UInputAction* UDataAsset_InputConfig::FindNativeInputActionByTag(FGameplayTag Tag)const 
{
	for (const FWuwaInputActionConfig& config : NativeInputActions)
	{
		if (config.InputTag == Tag && config.InputAction)
		{
			return config.InputAction;
		}
	}
	return nullptr;
}
