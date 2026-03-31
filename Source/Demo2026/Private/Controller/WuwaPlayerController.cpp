// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/WuwaPlayerController.h"


AWuwaPlayerController::AWuwaPlayerController()
{
	PlayerTeamID = FGenericTeamId(0);
}

FGenericTeamId AWuwaPlayerController::GetGenericTeamId() const
{
	return PlayerTeamID;
}
