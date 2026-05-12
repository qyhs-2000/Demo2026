// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "DemoDeveloperSettings.generated.h"

/**
 * 
 */
UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Game Data Tables"))
class DEMO2026_API UDemoDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config,EditAnywhere, BlueprintReadOnly, Category = "DataTable")
	TSoftObjectPtr<UDataTable> DT_UnitDefinition;

	UPROPERTY(Config,EditAnywhere, BlueprintReadOnly, Category = "DataTable")
	TSoftObjectPtr<UDataTable> DT_UnitAbilityMap;

	UPROPERTY(Config,EditAnywhere, BlueprintReadOnly, Category = "DataTable")
	TSoftObjectPtr<UDataTable> DT_StatProfile;

	UPROPERTY(Config,EditAnywhere, BlueprintReadOnly, Category = "DataTable")
	TSoftObjectPtr<UDataTable> DT_AttackHitConfig;

	UPROPERTY(Config,EditAnywhere, BlueprintReadOnly, Category = "DataTable")
	TSoftObjectPtr<UDataTable> DT_ProjectileConfig;

	UPROPERTY(Config,EditAnywhere, BlueprintReadOnly, Category = "CurveTable")
	TSoftObjectPtr<UCurveTable> DT_StatGrowth;
};
