// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/WuwaBaseCharater.h"
#include "Interfaces/Enemy/EnemyInterface.h"
#include "Components/TimelineComponent.h"
#include "WuwaEnemyCharater.generated.h"

/**
 *
 */

class UWidgetComponent;
class UEnemyUIComponent;
class UEnemyCombatComponent;

UCLASS()
class DEMO2026_API AWuwaEnemyCharacter : public AWuwaBaseCharacter, public IEnemyInterface
{
	GENERATED_BODY()
public:
	AWuwaEnemyCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void InitEnemyStartUpData();
	virtual void OnCharacterDeath() override;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* EnemyHealthWidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UEnemyUIComponent* EnemyUIComponent;

	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	virtual UPawnCombatComponent* GetPawnCombatComponent()const override;
#pragma region Timeline
	FTimeline DeathDissolveTimeline;
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	class UCurveFloat* TimelineCurve;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Dissolve")
	FName DissolveParamterName;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Dissolve")
	FName WeaponDissolveParamterName;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Combat")
	UEnemyCombatComponent* EnemyCombatComponent;

	UFUNCTION()
	void UpdateDissolveMaterialParams(float Amount);
	UFUNCTION()
	void DissolveTimelineFinished();
#pragma endregion

};
