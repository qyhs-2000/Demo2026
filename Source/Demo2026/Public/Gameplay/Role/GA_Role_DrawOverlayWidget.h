// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/WuwaRoleGameplayAbility.h"
#include "Widgets/WuwaWidgetBase.h"
#include "GA_Role_DrawOverlayWidget.generated.h"

/**
 * 
 */

//class UWuwaWidgetBase;

UCLASS()
class DEMO2026_API UGA_Role_DrawOverlayWidget : public UWuwaRoleGameplayAbility
{
	GENERATED_BODY()
public:
	UGA_Role_DrawOverlayWidget();
	virtual void OnAbilityActivate() override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI Class")
	TSubclassOf<UWuwaWidgetBase> OverlayWidgetClass;

	UWuwaWidgetBase* OverlayWidget = nullptr;
};
