// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/NotifyState/AnimNotifyState_DisplayActor.h"
#include "Character/WuwaBaseCharater.h"
#include "Weapon/WuwaWeaponBase.h"
void UAnimNotifyState_DisplayWeapon::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (AWuwaBaseCharacter * OwnerCharacter = Cast<AWuwaBaseCharacter>(MeshComp->GetOwner()))
	{
		if (AWuwaWeaponBase* TargetWeapon = OwnerCharacter->GetCurrentWeaponByType(WeaponType))
		{
			CachedWeapon = TargetWeapon;
			CachedWeapon->SetActorHiddenInGame(false);
		}
	}

}

void UAnimNotifyState_DisplayWeapon::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{

	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if (CachedWeapon)
	{
		CachedWeapon->SetActorHiddenInGame(true);
	}
}
