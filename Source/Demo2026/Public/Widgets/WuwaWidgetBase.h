// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WuwaWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class DEMO2026_API UWuwaWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;
	void InitEnemyCreateWidget(AActor* OwningEnemyActor);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Enemy UI Component Initialized"))
	void BP_OnOwningEnemyUIComponentInitialized(UEnemyUIComponent* EnemyUIComponent);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Role UI Component Initialized"))
	void BP_OnOwningRoleUIComponentInitialized(URoleUIComponent* RoleUIComponent);
};
