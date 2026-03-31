// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/NotifyState/ANS_ToggleWeaponCollision.h"
#include "Character/WuwaBaseCharater.h"
#include "Weapon/WuwaWeaponBase.h"
#include "Components/PawnCombatComponent.h"
void UANS_ToggleWeaponCollision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if (AWuwaBaseCharacter* Character = Cast<AWuwaBaseCharacter>(MeshComp->GetOwner()))
	{
		Character->GetPawnCombatComponent()->ToggleWeaponCollision(ToggleWeapon,ECollisionEnabled::QueryOnly);
	}

}

void UANS_ToggleWeaponCollision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if (AWuwaBaseCharacter* Character = Cast<AWuwaBaseCharacter>(MeshComp->GetOwner()))
	{
		Character->GetPawnCombatComponent()->ToggleWeaponCollision(ToggleWeapon,ECollisionEnabled::NoCollision);
	}
}
