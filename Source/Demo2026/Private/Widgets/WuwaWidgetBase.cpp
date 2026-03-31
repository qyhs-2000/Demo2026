// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/WuwaWidgetBase.h"
#include "Interfaces/PawnUIInterface.h"
#include "Components/UI/RoleUIComponent.h"
#include "Components/UI/EnemyUIComponent.h"

void UWuwaWidgetBase::NativeOnInitialized()
{
	if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(GetOwningPlayerPawn()))
	{
		if (URoleUIComponent* RoleUIComponent = Cast<URoleUIComponent>(PawnUIInterface->GetPawnUIComponent()))
		{
			BP_OnOwningRoleUIComponentInitialized(RoleUIComponent);
		}
	}
}

void UWuwaWidgetBase::InitEnemyCreateWidget(AActor* OwningEnemyActor)
{
	if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(OwningEnemyActor))
	{
		UEnemyUIComponent* EnemyUIComponent = Cast<UEnemyUIComponent>(PawnUIInterface->GetPawnUIComponent());
		check(EnemyUIComponent);
		BP_OnOwningEnemyUIComponentInitialized(EnemyUIComponent);
	}
}
