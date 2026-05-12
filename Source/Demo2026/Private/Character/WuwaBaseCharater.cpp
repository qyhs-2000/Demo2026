// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WuwaBaseCharater.h"
#include "AbilitySystem/WuwaAbilitySystemComponent.h"
#include "Weapon/WuwaWeaponBase.h"
#include "Components/PawnCombatComponent.h"
#include "Components/UI/PawnUIComponent.h"
#include "AbilitySystem/WuwaAttributeSet.h"
#include "Components/TimeDilationManagerComponent.h"

// Sets default values
AWuwaBaseCharacter::AWuwaBaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WuwaAbilitySystemComponent = CreateDefaultSubobject<UWuwaAbilitySystemComponent>(TEXT("WuwaAbilitySystemComponent"));
	WuwaAbilitySystemComponent->SetIsReplicated(true);
	WuwaAbilitySystemComponent->SetReplicationMode(ASCReplicationMode);

	WuwaAttributeSet = CreateDefaultSubobject<UWuwaAttributeSet>(TEXT("WuwaAttributeSet"));

	TimeDilationManager = CreateDefaultSubobject<UTimeDilationManagerComponent>(TEXT("TimeDilationManager"));
}

void AWuwaBaseCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	if (WuwaAbilitySystemComponent)
	{
		
		WuwaAbilitySystemComponent->InitAbilityActorInfo(this, this);
	}


	if (UPawnUIComponent* UIComp = GetPawnUIComponent())
	{
		UIComp->InitializeComp(WuwaAbilitySystemComponent);
	}
}

// Called when the game starts or when spawned
void AWuwaBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (GetMesh())
	{
		GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	}
	SpawnWeapon();
	if (GetPawnCombatComponent())
	{
		for (AWuwaWeaponBase* SpawnedWeapon : LoadedWeapons)
		{
			GetPawnCombatComponent()->RegisterSpawnedWeapon(SpawnedWeapon);

		}
	}

	if(WuwaAttributeSet)
	{
		WuwaAttributeSet->InitializeAttributes();
	}
}

void AWuwaBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (WuwaAbilitySystemComponent)
	{
		WuwaAbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
	GetPawnUIComponent()->InitializeComp(WuwaAbilitySystemComponent);
}

void AWuwaBaseCharacter::SpawnWeapon()
{
	if (AttachedWeaponsBP.IsEmpty()) return;
	if (UWorld* World = GetWorld())
	{
		for (FWeaponWithAttachedSocketName& WeaponClassWithSocketName : AttachedWeaponsBP)
		{
			FActorSpawnParameters SpawnParamters;
			SpawnParamters.Owner = this;
			SpawnParamters.Instigator = this;
			AWuwaWeaponBase* SpawnedWeapon = World->SpawnActor<AWuwaWeaponBase>(WeaponClassWithSocketName.WeaponClass, FTransform::Identity, SpawnParamters);
			SpawnedWeapon->SetActorHiddenInGame(true);
			if (WeaponClassWithSocketName.AttachedSocketName.IsValid())
			{
				FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepRelative, true);

				SpawnedWeapon->AttachToComponent(GetMesh(), AttachmentRules, WeaponClassWithSocketName.AttachedSocketName);
			}
			LoadedWeapons.AddUnique(SpawnedWeapon);
		}
	}
}

AWuwaWeaponBase* AWuwaBaseCharacter::GetCurrentWeaponByType(EWeaponType InWeaponType)
{
	for (AWuwaWeaponBase* Weapon : LoadedWeapons)
	{
		if (Weapon->WeaponType == InWeaponType)
		{
			return Weapon;
		}
	}
	return nullptr;
}

UPawnCombatComponent* AWuwaBaseCharacter::GetPawnCombatComponent() const
{
	return nullptr;
}

UPawnUIComponent *AWuwaBaseCharacter::GetPawnUIComponent() const
{
	return nullptr;
}

// Called to bind functionality to input
void AWuwaBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

