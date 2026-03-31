// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EWeaponType :uint8
{
    Weapon_None UMETA(DisplayName = "None"),
    Weapon_Gun_Left UMETA(DisplayName = "Left Gun"),
    Weapon_Gun_Right UMETA(DisplayName = "Right Gun"),

    Weapon_Enemy_Guardian_Stick UMETA(DisplayName = "Enemy Guardian Stick"),
    Weapon_Max UMETA(DisplayName = "MAX")
};


UENUM(BlueprintType)
enum class EWuwaSuccessType :uint8
{
    Successful,
    Failed
};