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

DECLARE_MULTICAST_DELEGATE(FOnMoveInput);

UCLASS()
class DEMO2026_API AWuwaPlayerCharater : public AWuwaBaseCharater
{
	GENERATED_BODY()
public:
	AWuwaPlayerCharater();
	void AbilityInputPressed(FGameplayTag InputTag);
	void AbilityInputReleased(FGameplayTag InputTag);

	FOnMoveInput OnMoveInput;
protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UDataAsset_InputConfig* InputConfig;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr< UDataAsset_RoleStartUp > RoleStartUpData;

	void InputLook(const FInputActionValue& InputValue);
	void InputMove(const FInputActionValue& InputValue);

	
private:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
};
