// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "DataAsset_InputConfig.generated.h"

class UInputMappingContext;
class UInputAction;
/**
 * 
 */

USTRUCT(BlueprintType)
struct FWuwaInputActionConfig
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	FGameplayTag InputTag;

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	UInputAction *InputAction;

	inline bool IsValid()const
	{
		return InputTag.IsValid() && InputAction;
	}

};

UCLASS()
class DEMO2026_API UDataAsset_InputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputMappingContext *DefaultInputMappingContext;

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	TArray<FWuwaInputActionConfig> NativeInputActions;

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly)
	TArray<FWuwaInputActionConfig> AbilityInputActions;

	UInputAction* FindNativeInputActionByTag(FGameplayTag Tag) const;
};
