// Fill out your copyright notice in the Description page of Project Settings.


#include "WuwaBlueprintFunctionLibrary.h"
#include "AbilitySystem/WuwaAbilitySystemComponent.h"
#include "Character/WuwaBaseCharater.h"
#include "GenericTeamAgentInterface.h"
bool UWuwaBlueprintFunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
	if (!TargetPawn || !QueryPawn)
	{
		return false;
	}
	IGenericTeamAgentInterface* QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());
	if (QueryTeamAgent && TargetTeamAgent)
	{
		return QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
	}
	return false;
}

UWuwaAbilitySystemComponent* UWuwaBlueprintFunctionLibrary::GetASCFromActorInfo(AActor * InActor)
{
	check(InActor);
	return CastChecked<AWuwaBaseCharacter>(InActor)->GetWuwaAbilitySystemComponent();
}

void UWuwaBlueprintFunctionLibrary::AddGameplayTagToActorIfNone(AActor* TargetActor, FGameplayTag TagToAdd)
{
	UWuwaAbilitySystemComponent* ASC = GetASCFromActorInfo(TargetActor);
	if (!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

bool UWuwaBlueprintFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag Tag)
{
	UWuwaAbilitySystemComponent* ASC = GetASCFromActorInfo(InActor);
	if (ASC)
	{
		return ASC->HasMatchingGameplayTag(Tag);
	}
	return false;
}

