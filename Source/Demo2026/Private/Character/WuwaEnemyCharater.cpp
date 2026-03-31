// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WuwaEnemyCharater.h"
#include "Engine/AssetManager.h"
#include "DataAssets/DataAsset_StartUpBase.h"
#include "Components/WidgetComponent.h"
#include "Components/UI/EnemyUIComponent.h"
#include "Components/EnemyCombatComponent.h"
#include "Widgets/WuwaWidgetBase.h"
#include "Curves/CurveFloat.h"
#include "Weapon/WuwaWeaponBase.h"
#include "DebugHelper.h"

AWuwaEnemyCharacter::AWuwaEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	EnemyHealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("EnemyHealthWidgetComponent"));
	EnemyHealthWidgetComponent->SetupAttachment(GetMesh());

	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>(TEXT("EnemyCombatComponent"));
	EnemyUIComponent = CreateDefaultSubobject<UEnemyUIComponent>(TEXT("EnemyUIComponent"));
	
}

void AWuwaEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitEnemyStartUpData();
}

void AWuwaEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (UWuwaWidgetBase* EnemyWidget = Cast<UWuwaWidgetBase>(EnemyHealthWidgetComponent->GetUserWidgetObject()))
	{
		EnemyWidget->InitEnemyCreateWidget(this);
	}

	if (TimelineCurve)
	{
		FOnTimelineFloatStatic UpdateCallback;
		UpdateCallback.BindUFunction(this,  TEXT("UpdateDissolveMaterialParams"));
		FOnTimelineEventStatic PlayFinishedFS;
		PlayFinishedFS.BindUFunction(this, TEXT("DissolveTimelineFinished"));

		DeathDissolveTimeline.AddInterpFloat(TimelineCurve, UpdateCallback);
		DeathDissolveTimeline.SetTimelineFinishedFunc(PlayFinishedFS);
	}
}

void AWuwaEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DeathDissolveTimeline.TickTimeline(DeltaTime);
}

void AWuwaEnemyCharacter::InitEnemyStartUpData()
{
	if (CharacterStartUpData.IsNull()) return;
	int AbilityApplyLevel = 1;
	UAssetManager::GetStreamableManager().RequestAsyncLoad(CharacterStartUpData.ToSoftObjectPath(), FStreamableDelegate::CreateLambda([this, AbilityApplyLevel]() {
		if (UDataAsset_StartUpBase* LoadedData = CharacterStartUpData.Get())
		{
			LoadedData->GiveAbilityToAbilitSystemComponent(WuwaAbilitySystemComponent, AbilityApplyLevel);
		}
		}));

}

void AWuwaEnemyCharacter::OnCharacterDeath()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		GetMesh()->bPauseAnims = true;
	}

	SetActorEnableCollision(false);
	DeathDissolveTimeline.PlayFromStart();
	if (EnemyHealthWidgetComponent)
	{
		EnemyHealthWidgetComponent->SetVisibility(false);
		EnemyHealthWidgetComponent->SetHiddenInGame(true);
	}

}

UPawnUIComponent* AWuwaEnemyCharacter::GetPawnUIComponent() const
{
	return EnemyUIComponent;
}

UPawnCombatComponent* AWuwaEnemyCharacter::GetPawnCombatComponent() const
{
	return EnemyCombatComponent;
}

void AWuwaEnemyCharacter::UpdateDissolveMaterialParams(float Amount)
{
	GetMesh()->SetScalarParameterValueOnMaterials(DissolveParamterName, Amount);

	for (AWuwaWeaponBase* Weapon : GetPawnCombatComponent()->GetSpawnedWeapons())
	{
		if (UMeshComponent* WeaponMesh = Weapon->GetMesh())
		{
			WeaponMesh->SetScalarParameterValueOnMaterials(WeaponDissolveParamterName, Amount);
		}
	}
}

void AWuwaEnemyCharacter::DissolveTimelineFinished()
{
	Destroy();
	for (AWuwaWeaponBase* Weapon : GetPawnCombatComponent()->GetSpawnedWeapons())
	{
		Weapon->Destroy();
	}
}
