// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/WuwaCharacterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/WuwaBaseCharater.h"
#include "KismetAnimationLibrary.h"
void UWuwaCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<AWuwaBaseCharater>(TryGetPawnOwner());
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

	LocomotionDirection = UKismetAnimationLibrary::CalculateDirection(OwningCharacter->GetVelocity(), OwningCharacter->GetActorRotation());
}
