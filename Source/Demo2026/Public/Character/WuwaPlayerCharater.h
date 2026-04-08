// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/WuwaBaseCharater.h"
#include "GameplayTagContainer.h"
#include "WuwaPlayerCharater.generated.h"

/**
 *
 */

class USpringArmComponent;
class UCameraComponent;
class UDataAsset_InputConfig;
struct FInputActionValue;
class UDataAsset_RoleStartUp;
class URoleCombatComponent;
class URoleUIComponent;
class UPostProcessComponent;

DECLARE_MULTICAST_DELEGATE(FOnMoveInput);

UCLASS()
class DEMO2026_API AWuwaPlayerCharater : public AWuwaBaseCharacter
{
	GENERATED_BODY()
public:
	AWuwaPlayerCharater();
	void AbilityInputPressed(FGameplayTag InputTag);
	void AbilityInputReleased(FGameplayTag InputTag);
	virtual void BeginPlay() override;

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerAbilityInputPressed(FGameplayTag InputTag);
	FOnMoveInput OnMoveInput;

	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	virtual UPawnUIComponent* GetPawnUIComponent() const override;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Components")
	UPostProcessComponent *MatrixPostProcess;
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDataAsset_InputConfig* InputConfig;

	void InputLook(const FInputActionValue& InputValue);
	void InputMove(const FInputActionValue& InputValue);
	void Input_SwitchTargetTrigger(const FInputActionValue& InputValue);
	void Input_SwitchTargetCompleted(const FInputActionValue& InputValue);
	FVector2D SwitchDirection = FVector2D::Zero();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
	URoleCombatComponent* RoleCombatComponent;

private:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	URoleUIComponent* RoleUIComponent;

};
