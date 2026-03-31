// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WuwaWeaponBase_StaticMesh.h"
#include "Components/BoxComponent.h"

AWuwaWeaponBase_StaticMesh::AWuwaWeaponBase_StaticMesh()
{

	WeaponMesh_StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UStaticMeshComponent"));
	SetRootComponent(WeaponMesh_StaticMesh);

	WeaponCollisionBox->SetupAttachment(GetRootComponent());
}

UMeshComponent* AWuwaWeaponBase_StaticMesh::GetMesh()
{
	return WeaponMesh_StaticMesh;
}
