// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/WuwaRoleGameplayAbility.h"
#include "Widgets/WuwaWidgetBase.h"
#include "GA_TargetLock.generated.h"

/**
 * 
 */

class UInputMappingContext;

UCLASS()
class DEMO2026_API UGA_TargetLock : public UWuwaRoleGameplayAbility
{
	GENERATED_BODY()
public:
	virtual void OnAbilityActivate() override;
	virtual void OnEndAbility() override;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputMappingContext* IMC_TargetLock;

	void InitTargetLockInputMappingContext();
	void RemoveTargetLockInputMappingContext();
	void TryLockTargetCharacter();
	void GetAvailableTargetLockActors();
	void CancelTargetLockAbility();
	AActor* GetNearestTargetFromAvailableActors(const TArray<AActor*> & InAvailableActors);
	void SetTargetLockWidgetPosition();
	void InitTargetLockMovement();
	void ResetTargetLockMovement();
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	float TargetLockCameraOffset = 20.f;

	UPROPERTY()
	FVector2D TargetLockBoxSize = FVector2D::ZeroVector;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	float RotateToTargetLockSpeed = 5.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Warrior|Target Lock")
	float BoxTraceDistance = 2000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Warrior|Target Lock")
	TArray<TEnumAsByte<	EObjectTypeQuery> > BoxTraceChannel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Warrior|Target Lock")
	FVector BoxTraceSize = FVector(5000.f,5000.f,300.f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Warrior|Target Lock")
	bool bShowPersistentDebugShape = false;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<UWuwaWidgetBase> TargetLockWidgetClass;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float TargetLockWalkSpeed = 100.f;

	UWuwaWidgetBase* TargetLockWidget;

	UFUNCTION(BlueprintCallable)
	void OnTargetLockTick(float DeltaTime);

	UFUNCTION()
	void OnSwitchTarget(FGameplayEventData Payload);

	void GetAvailableActorsAroundCurrentLockedActor(TArray<AActor*>& ActorsOnLeft, TArray<AActor*>& ActorsOnRight);

	void DrawTargetLockWidget();
protected:
	TWeakObjectPtr<AActor> CurrentLockedActor;
	TArray<AActor*> AvailableActors;
	float CachedMaxWalkSpeed;
};
