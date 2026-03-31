// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Data/EnumTypes.h"
#include "Interfaces/PawnUIInterface.h"
#include "AbilitySystemComponent.h"
#include "WuwaBaseCharater.generated.h"

class UWuwaAbilitySystemComponent;
class AWuwaWeaponBase;
class UPawnCombatComponent;
class UWuwaAttributeSet;
class UDataAsset_StartUpBase;
class UTimeDilationManagerComponent;

USTRUCT(BlueprintType)
struct FWeaponWithAttachedSocketName
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AWuwaWeaponBase> WeaponClass;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon")
	FName AttachedSocketName;
};

UCLASS()
class DEMO2026_API AWuwaBaseCharacter : public ACharacter,public IPawnUIInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWuwaBaseCharacter();
	FORCEINLINE UWuwaAbilitySystemComponent* GetWuwaAbilitySystemComponent()const { return WuwaAbilitySystemComponent; }
	virtual void OnCharacterDeath() {};
	virtual void OnRep_PlayerState() override;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "TimeDilation")
	UTimeDilationManagerComponent* TimeDilationManager;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "AbilitySystem")
	UWuwaAbilitySystemComponent* WuwaAbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "AbilitySystem")
	UWuwaAttributeSet* WuwaAttributeSet;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "AbilitySystem")
	EGameplayEffectReplicationMode ASCReplicationMode = EGameplayEffectReplicationMode::Mixed;


	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Weapon")
	TArray<FWeaponWithAttachedSocketName> AttachedWeaponsBP;

	//Loaded Weapons
	TArray<AWuwaWeaponBase*> LoadedWeapons;
	virtual void SpawnWeapon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterData")
	TSoftObjectPtr<UDataAsset_StartUpBase> CharacterStartUpData;

	
public:	
	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	AWuwaWeaponBase* GetCurrentWeaponByType(EWeaponType InWeaponType);

	virtual UPawnCombatComponent* GetPawnCombatComponent() const;

	virtual UPawnUIComponent *GetPawnUIComponent() const override;
};
