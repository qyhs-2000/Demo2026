// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/NotifyState/ANS_WeaponTrace.h"
#include "Character/WuwaBaseCharater.h"
#include "Components/PawnCombatComponent.h"
#include "Weapon/WuwaWeaponBase.h"
void UANS_WeaponTrace::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	AWuwaBaseCharacter* Character = Cast<AWuwaBaseCharacter>(MeshComp->GetOwner());
	if (!Character)
	{
		return;
	}
	UPawnCombatComponent* CombatComponent = Character->GetPawnCombatComponent();
	Weapon = CombatComponent->GetWeaponByWeaponType(WeaponType);
	if (Weapon)
	{
		LastTimeSocketStartLocation = Weapon->GetSocketLocation(TraceStartSocketName);
		LastTimeSocketEndLocation = Weapon->GetSocketLocation(TraceSocketEndName);
	}
}

void UANS_WeaponTrace::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	
	if (Weapon == nullptr)
	{
		return;
	}
	
	FVector CurrentSocketStartLoc = Weapon->GetSocketLocation(TraceStartSocketName);
	FVector CurrentSocketEndLoc = Weapon->GetSocketLocation(TraceSocketEndName);
	TArray<FHitResult> AllHitActors;
	TArray<FHitResult> TmpHitActors;
	if (MeshComp->GetWorld())
	{
		ECollisionChannel CollisionChannel = ECollisionChannel::ECC_Pawn;
		FCollisionShape CollisionShape = FCollisionShape::MakeSphere(TraceSphereRadius);
		MeshComp->GetWorld()->SweepMultiByChannel(TmpHitActors, LastTimeSocketStartLocation, CurrentSocketStartLoc, FQuat::Identity, CollisionChannel, CollisionShape);
		AllHitActors.Append(TmpHitActors);
		TmpHitActors.Empty();
		MeshComp->GetWorld()->SweepMultiByChannel(TmpHitActors, LastTimeSocketEndLocation, CurrentSocketEndLoc, FQuat::Identity, CollisionChannel, CollisionShape);
		AllHitActors.Append(TmpHitActors);
	}
	for (const FHitResult& HitResult : AllHitActors)
	{
		AActor* Target = HitResult.GetActor();
		if (Target && Target != MeshComp->GetOwner() && !HitActors.Contains(Target))
		{
			HitActors.Add(Target);
			Weapon->HitActor(Target);
		}
	}
	LastTimeSocketStartLocation = CurrentSocketStartLoc;
	LastTimeSocketEndLocation = CurrentSocketEndLoc;
}

void UANS_WeaponTrace::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	HitActors.Empty();
}
