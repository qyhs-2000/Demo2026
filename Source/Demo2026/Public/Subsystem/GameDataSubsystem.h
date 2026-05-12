// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Table/TableRows.h"
#include "GameDataSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class DEMO2026_API UGameDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UDataTable* DT_UnitDefinition;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UDataTable* DT_UnitAbilityMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UDataTable* DT_StatProfile;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UDataTable* DT_AttackHitConfig;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UDataTable* DT_ProjectileConfig;	

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UCurveTable* DT_StatGrowth;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	FUnitDefinitionRow* GetUnitDefinitionByID(const FName& UnitID) const;
	FStatProfileRow* GetStatProfileByID(const FName& StatProfileID) const;
	
	float GetAttackPowerGrowthByLevel(const APawn * Pawn, int32 Level) const;
	float GetBaseAttackPowerByUnitID(const FName& UnitID) const;
};

