// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/TGGameModeBase.h"
#include "Player/TGPlayer.h"
#include "Player/TGPlayerController.h"

ATGGameModeBase::ATGGameModeBase()
{
	DefaultPawnClass = ATGPlayer::StaticClass();
	PlayerControllerClass = ATGPlayerController::StaticClass();
}
