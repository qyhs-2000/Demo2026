// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WuwaWeaponBase_SkeletalMesh.h"
#include "Components/BoxComponent.h"

AWuwaWeaponBase_SkeletalMesh::AWuwaWeaponBase_SkeletalMesh()
{
	WeaponMesh_SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("USkeletalMeshComponent"));
	SetRootComponent(WeaponMesh_SkeletalMesh);

	WeaponCollisionBox->SetupAttachment(GetRootComponent());
}

UMeshComponent* AWuwaWeaponBase_SkeletalMesh::GetMesh()
{
	return WeaponMesh_SkeletalMesh;
}
