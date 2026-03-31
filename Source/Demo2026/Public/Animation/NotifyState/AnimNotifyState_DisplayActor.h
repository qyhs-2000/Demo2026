// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Data/EnumTypes.h"
#include "AnimNotifyState_DisplayActor.generated.h"

/**
 * 
 */

class AWuwaWeaponBase;

UCLASS()
class DEMO2026_API UAnimNotifyState_DisplayWeapon : public UAnimNotifyState
{
	GENERATED_BODY()
	
protected:
	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, const FAnimNotifyEventReference& EventReference);

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EWeaponType WeaponType = EWeaponType::Weapon_None;

private:
	AWuwaWeaponBase* CachedWeapon = nullptr;
};
