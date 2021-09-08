// Copyright Epic Games, Inc. All Rights Reserved.


#include "DotGameGameModeBase.h"
#include "MyPlayerController.h"
#include "MyGameState.h"

ADotGameGameModeBase::ADotGameGameModeBase()
{
	PlayerControllerClass = AMyPlayerController::StaticClass();
	GameStateClass = AMyGameState::StaticClass();
	DefaultPawnClass = nullptr;

}