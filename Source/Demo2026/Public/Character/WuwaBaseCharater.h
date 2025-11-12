// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WuwaBaseCharater.generated.h"

class UWuwaAbilitySystemComponent;

UCLASS()
class DEMO2026_API AWuwaBaseCharater : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWuwaBaseCharater();
	FORCEINLINE UWuwaAbilitySystemComponent* GetWuwaAbilitySystemComponent()const { return WuwaAbilitySystemComponent; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "AbilitySystem")
	UWuwaAbilitySystemComponent* WuwaAbilitySystemComponent;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
