// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *
 */
namespace debug
{
	static void Print(const FString& msg, const FColor& color = FColor::MakeRandomColor(), int key = -1)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(key, 7.f, color, msg);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *msg);
		}
	}

	static void Print(AActor* Actor, const FString& msg, const FColor& color = FColor::MakeRandomColor(), int key = -1)
	{
		if (GEngine)
		{
			if (Actor->GetLocalRole() < ROLE_Authority)
			{
				const FString& newString = FString(TEXT("Client : ")) + msg;
				GEngine->AddOnScreenDebugMessage(key, 7.f, color, msg);
				UE_LOG(LogTemp, Warning, TEXT("%s"), *newString);
			}
			else
			{
				const FString& newString = FString(TEXT("Server : ")) + msg;
				GEngine->AddOnScreenDebugMessage(key, 7.f, color, msg);
				UE_LOG(LogTemp, Warning, TEXT("%s"), *newString);
			}
		}
	}
}
