// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstance/WuwaBaseAnimInstance.h"
#include "WuwaCharacterAnimInstance.generated.h"

/**
 * 
 */

class AWuwaBaseCharater;
class UCharacterMovementComponent;
UCLASS()
class DEMO2026_API UWuwaCharacterAnimInstance : public UWuwaBaseAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wuwa|Anim")
	float GroundSpeed = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wuwa|Anim")
	float LocomotionDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wuwa|Anim")
	bool bHasAcceleration = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wuwa|Anim")
	TSoftObjectPtr<AWuwaBaseCharater> OwningCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wuwa|Anim")
	UCharacterMovementComponent* OwningCharacterMovement;
};
