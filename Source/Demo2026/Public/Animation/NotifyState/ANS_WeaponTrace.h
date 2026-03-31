// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Data/EnumTypes.h"
#include "ANS_WeaponTrace.generated.h"

/**
 * 
 */

class AWuwaWeaponBase;

UCLASS()
class DEMO2026_API UANS_WeaponTrace : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	FName TraceStartSocketName = "N_WeaponTrace";

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	FName TraceSocketEndName = "F_WeaponTrace";

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float TraceSphereRadius = 15.f;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	EWeaponType WeaponType = EWeaponType::Weapon_None;
	AWuwaWeaponBase* Weapon;
private:
	TArray<AActor*> HitActors;
	FVector LastTimeSocketStartLocation;
	FVector LastTimeSocketEndLocation;
};
