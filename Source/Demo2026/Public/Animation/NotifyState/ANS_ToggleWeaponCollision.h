// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Data/EnumTypes.h"
#include "ANS_ToggleWeaponCollision.generated.h"

/**
 * 
 */
UCLASS()
class DEMO2026_API UANS_ToggleWeaponCollision : public UAnimNotifyState
{
	GENERATED_BODY()
	
protected:
	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, const FAnimNotifyEventReference& EventReference);

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	EWeaponType ToggleWeapon = EWeaponType::Weapon_None;
};
