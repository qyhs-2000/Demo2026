// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/GameDataSubsystem.h"

#include "Settings/DemoDeveloperSettings.h"
#include "Engine/DataTable.h"
#include "Engine/CurveTable.h" 
#include "Character/WuwaBaseCharater.h"

void UGameDataSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    const UDemoDeveloperSettings* DeveloperSettings = GetDefault<UDemoDeveloperSettings>();
    if (DeveloperSettings)
    {
        DT_UnitDefinition = DeveloperSettings->DT_UnitDefinition.LoadSynchronous();
        DT_UnitAbilityMap = DeveloperSettings->DT_UnitAbilityMap.LoadSynchronous();
        DT_StatProfile = DeveloperSettings->DT_StatProfile.LoadSynchronous();
        DT_AttackHitConfig = DeveloperSettings->DT_AttackHitConfig.LoadSynchronous();
        DT_ProjectileConfig = DeveloperSettings->DT_ProjectileConfig.LoadSynchronous();
        DT_StatGrowth = DeveloperSettings->DT_StatGrowth.LoadSynchronous();
    }
}

FUnitDefinitionRow* UGameDataSubsystem::GetUnitDefinitionByID(const FName& UnitID) const
{
    if (!DT_UnitDefinition)
    {
        UE_LOG(LogTemp, Warning, TEXT("UGameDataSubsystem::GetUnitDefinitionByID: DT_UnitDefinition is null"));
        return nullptr;
    }

    return DT_UnitDefinition->FindRow<FUnitDefinitionRow>(UnitID, FString());
}

FStatProfileRow* UGameDataSubsystem::GetStatProfileByID(const FName& StatProfileID) const
{
    if (!DT_StatProfile)
    {
        UE_LOG(LogTemp, Warning, TEXT("UGameDataSubsystem::GetStatProfileByID: DT_StatProfile is null"));
        return nullptr;
    }

    return DT_StatProfile->FindRow<FStatProfileRow>(StatProfileID, FString());
}

float UGameDataSubsystem::GetAttackPowerGrowthByLevel(const APawn * Pawn, int32 Level) const
{
    const AWuwaBaseCharacter* Character = Cast<AWuwaBaseCharacter>(Pawn);
    if (!Character || Character->UnitId == NAME_None)    {
        UE_LOG(LogTemp, Warning, TEXT("GetAttackPowerGrowthByLevel: Pawn is not a AWuwaBaseCharacter"));
        return 0.f;
    }
    if (!IsValid(DT_StatGrowth))
    {
        UE_LOG(LogTemp, Warning, TEXT("DT_StatGrowth is null"));
        return 0.f;
    }

    FName StatProfileID = GetUnitDefinitionByID(Character->UnitId)->StatProfileId;

    FName RowName = GetStatProfileByID(StatProfileID)->AttackCurveRow;
    FString RowNameString = RowName.ToString();
    static const FString Context(TEXT("GetAttackPowerGrowthByLevel"));
    UE_LOG(LogTemp, Warning, TEXT("RowName: %s"), *RowNameString);
    FRealCurve* FoundCurveBase = DT_StatGrowth->FindCurve(RowName, Context);
    UE_LOG(LogTemp, Log, TEXT("CurveBase Pointer Address: %p"), FoundCurveBase);

    if (FoundCurveBase)
    {
        return FoundCurveBase->Eval(static_cast<float>(Level));
    }

    return 0.f;
}

float UGameDataSubsystem::GetBaseAttackPowerByUnitID( const FName& UnitID) const
{
    FUnitDefinitionRow* UnitDef = GetUnitDefinitionByID(UnitID);
    if (!UnitDef)
    {
        UE_LOG(LogTemp, Warning, TEXT("GetBaseAttackPowerByUnitID: No unit definition found for UnitID %s"), *UnitID.ToString());
        return 0.f;
    }

    FStatProfileRow* StatProfile = GetStatProfileByID(UnitDef->StatProfileId);
    if (!StatProfile)
    {
        UE_LOG(LogTemp, Warning, TEXT("GetBaseAttackPowerByUnitID: No stat profile found for StatProfileId %s"), *UnitDef->StatProfileId.ToString());
        return 0.f;
    }

    return StatProfile->BaseAttackPower;
}