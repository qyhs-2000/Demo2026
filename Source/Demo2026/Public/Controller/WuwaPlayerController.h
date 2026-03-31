// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "WuwaPlayerController.generated.h"

/**
 * 
 */


UCLASS()
class DEMO2026_API AWuwaPlayerController : public APlayerController,public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
public:
	AWuwaPlayerController();
	virtual FGenericTeamId GetGenericTeamId() const override;
protected:
	FGenericTeamId PlayerTeamID;
};
