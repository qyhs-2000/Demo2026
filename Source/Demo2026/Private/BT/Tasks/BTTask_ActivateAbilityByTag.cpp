// Fill out your copyright notice in the Description page of Project Settings.


#include "BT/Tasks/BTTask_ActivateAbilityByTag.h"
#include "Controller/WuwaAIController.h"
#include "Character/WuwaBaseCharater.h"
#include "AbilitySystem/WuwaAbilitySystemComponent.h"
EBTNodeResult::Type UBTTask_ActivateAbilityByTag::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AWuwaAIController* EnemyAIController = Cast<AWuwaAIController>(OwnerComp.GetOwner()))
	{
		if (AWuwaBaseCharacter* BaseCharacter = Cast<AWuwaBaseCharacter>(EnemyAIController->GetPawn()))
		{
			UWuwaAbilitySystemComponent* ASC = BaseCharacter->GetWuwaAbilitySystemComponent();
			return ASC->TryActivateAbilityByTag(AbilityTagToActivate) ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;

		}

	}
	return EBTNodeResult::Failed;
}
