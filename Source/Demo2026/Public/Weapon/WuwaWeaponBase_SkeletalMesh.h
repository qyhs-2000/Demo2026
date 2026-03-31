// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/WuwaWeaponBase.h"
#include "WuwaWeaponBase_SkeletalMesh.generated.h"

/**
 * 
 */
UCLASS()
class DEMO2026_API AWuwaWeaponBase_SkeletalMesh : public AWuwaWeaponBase
{
	GENERATED_BODY()
public:
	AWuwaWeaponBase_SkeletalMesh();
	virtual UMeshComponent* GetMesh() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	USkeletalMeshComponent* WeaponMesh_SkeletalMesh;
};
