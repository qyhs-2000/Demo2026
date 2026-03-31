// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/WuwaCharacterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/WuwaBaseCharater.h"
#include "AbilitySystem/WuwaAbilitySystemComponent.h"
#include "KismetAnimationLibrary.h"
void UWuwaCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<AWuwaBaseCharacter>(TryGetPawnOwner());
	if (OwningCharacter)
	{
		OwningCharacterMovement = Cast<UCharacterMovementComponent>(OwningCharacter->GetCharacterMovement());
	}
}

void UWuwaCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningCharacterMovement)
	{
		return;
	}
	GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	bHasAcceleration = OwningCharacterMovement->GetCurrentAcceleration().SizeSquared2D() > 0.f;
	bIsFalling = OwningCharacterMovement->IsFalling();
	LocomotionDirection = UKismetAnimationLibrary::CalculateDirection(OwningCharacter->GetVelocity(), OwningCharacter->GetActorRotation());
    /*if (GroundSpeed > 5.0f)
    {
        float RawTargetDirection = UKismetAnimationLibrary::CalculateDirection(
            OwningCharacter->GetVelocity(), 
            OwningCharacter->GetActorRotation()
        );

        const float DeadZoneDegrees = 10.0f; 

        if (FMath::Abs(RawTargetDirection) > (180.f - DeadZoneDegrees))
        {
            RawTargetDirection = 180.f; 
        }

        float DeltaAngle = FRotator::NormalizeAxis(RawTargetDirection - LocomotionDirection);

        LocomotionDirection = FRotator::NormalizeAxis(
            LocomotionDirection + FMath::FInterpTo(0.f, DeltaAngle, DeltaSeconds, DirectionInterpSpeed)
        );

    }*/
}

bool UWuwaCharacterAnimInstance::HasTag(FGameplayTag TagToCheck)
{
	if (!OwningCharacter)
	{
		return false;
	}
	return OwningCharacter->GetWuwaAbilitySystemComponent()->HasMatchingGameplayTag(TagToCheck);
}
