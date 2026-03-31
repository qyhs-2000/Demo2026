// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/WuwaBaseAnimInstance.h"
#include "WuwaBlueprintFunctionLibrary.h"
bool UWuwaBaseAnimInstance::DoesOwnerHaveTag(FGameplayTag Tag)
{
	APawn* Pawn = TryGetPawnOwner();
	if (Pawn)
	{
		return UWuwaBlueprintFunctionLibrary::NativeDoesActorHaveTag(Pawn,Tag);
	}
	return false;
}
