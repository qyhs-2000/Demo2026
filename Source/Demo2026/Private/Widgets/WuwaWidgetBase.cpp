// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/WuwaWidgetBase.h"
#include "Interfaces/PawnUIInterface.h"
#include "Components/UI/RoleUIComponent.h"
#include "Components/UI/EnemyUIComponent.h"
#include "Character/WuwaPlayerCharater.h"

void UWuwaWidgetBase::NativeOnInitialized()
{
	if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(GetOwningPlayerPawn()))
	{
		if (URoleUIComponent* RoleUIComponent = Cast<URoleUIComponent>(PawnUIInterface->GetPawnUIComponent()))
		{
			AWuwaPlayerCharater* PlayerCharacter = Cast<AWuwaPlayerCharater>(GetOwningPlayerPawn());
			if(PlayerCharacter)
			{
				RoleUIComponent->InitializeComp(PlayerCharacter->GetWuwaAbilitySystemComponent());
			}
			BP_OnOwningRoleUIComponentInitialized(RoleUIComponent);
		}
	}
}

void UWuwaWidgetBase::InitEnemyCreateWidget(AActor* OwningEnemyActor)
{
	if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(OwningEnemyActor))
	{
		AWuwaBaseCharacter * EnemyCharacter = Cast<AWuwaBaseCharacter>(OwningEnemyActor);
		if(EnemyCharacter)
		{
			PawnUIInterface->GetPawnUIComponent()->InitializeComp(EnemyCharacter->GetWuwaAbilitySystemComponent());
		}
		UEnemyUIComponent* EnemyUIComponent = Cast<UEnemyUIComponent>(PawnUIInterface->GetPawnUIComponent());
		check(EnemyUIComponent);

		BP_OnOwningEnemyUIComponentInitialized(EnemyUIComponent);
	}
}
