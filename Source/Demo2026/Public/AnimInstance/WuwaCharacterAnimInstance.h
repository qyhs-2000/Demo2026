// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstance/WuwaBaseAnimInstance.h"
#include "GameplayTagContainer.h"
#include "WuwaCharacterAnimInstance.generated.h"

/**
 * 
 */

class AWuwaBaseCharacter;
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Wuwa|Anim")
	bool bIsFalling = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wuwa|Anim")
	TSoftObjectPtr<AWuwaBaseCharacter> OwningCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wuwa|Anim")
	UCharacterMovementComponent* OwningCharacterMovement;

	UFUNCTION(BlueprintPure, Category = "Wuwa|Anim",meta = (BlueprintThreadSafe))
	bool HasTag(FGameplayTag TagToCheck);

protected:
	// 目标方向（瞬时计算值）
	float TargetLocomotionDirection = 0.f;

	// 插值速度，建议 8.0 - 12.0 之间，值越大响应越快，越小越平滑
	UPROPERTY(EditAnywhere, Category = "Locomotion")
	float DirectionInterpSpeed = 10.0f;
};
