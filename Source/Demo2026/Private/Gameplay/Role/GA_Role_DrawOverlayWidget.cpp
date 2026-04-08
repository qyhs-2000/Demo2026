// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Role/GA_Role_DrawOverlayWidget.h"
#include "Controller/WuwaPlayerController.h"
UGA_Role_DrawOverlayWidget::UGA_Role_DrawOverlayWidget()
{
	AbilityActivationPolicy = EWuwaGameplayAbilityActivationPolicy::OnGiven;
}

void UGA_Role_DrawOverlayWidget::OnAbilityActivate()
{
	if (!IsLocallyControlled())
	{
		EndAbility();
		return;
	}


	if (OverlayWidget == nullptr)
	{
		OverlayWidget = CreateWidget<UWuwaWidgetBase>(GetRoleControllerFromActorInfo(), OverlayWidgetClass);
		//check(OverlayWidget);
		OverlayWidget->AddToViewport();
	}
	EndAbility();
}
