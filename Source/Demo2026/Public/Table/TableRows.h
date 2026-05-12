// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "TableRows.generated.h"
/**
 * 
 */

USTRUCT(BlueprintType)
struct FUnitDefinitionRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName UnitId;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName StatProfileId;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName AbilityLoadoutId;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 DefaultLevel = 1;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName AssetProfileId;
};

USTRUCT(BlueprintType)
struct FUnitAbilityMapRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName AbilityLoadoutId;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 GrantOrder = 0;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName AbilityId;
};

USTRUCT(BlueprintType)
struct FStatProfileRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float BaseAttackPower = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float BaseDefensePower = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float BaseMaxHealth = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName AttackCurveRow;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName DefenseCurveRow;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName HealthCurveRow;
};

USTRUCT(BlueprintType)
struct FAttackHitConfigRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName AttackId;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 HitIndex = 1;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float DamageCoefficient = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float FlatDamage = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool bCanTriggerHitReact = true;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float HitReactStrength = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float KnockbackDistance = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName ProjectileId;
};

USTRUCT(BlueprintType)
struct FProjectileConfigRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName ProjectileId;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float MoveSpeed = 1000.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float LifeTime = 3.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float CollisionRadius = 20.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float ExplosionRadius = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool bCanPierce = false;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 MaxHitCount = 1;
};

USTRUCT(BlueprintType)
struct FStatGrowthRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    FRichCurve GrowthCurve;

};

