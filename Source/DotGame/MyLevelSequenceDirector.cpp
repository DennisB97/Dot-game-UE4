// Copyright Dennis Bäckström (C) 2021


#include "MyLevelSequenceDirector.h"
#include "MyGameState.h"
#include "Kismet/GameplayStatics.h"
#include "LevelStreamHandler.h"
#include "LevelSequencePlayer.h"

void UMyLevelSequenceDirector::PlayCountDownMedia()
{

	UWorld* World = GetWorld();

	if (!World)
	{
		UE_LOG(LogTemp, Warning, TEXT("World was nullptr!"));
		return;
	}

	// Forward to gamestate with the pointer to the tv actor in world and start media
	if (AMyGameState* MyGameState = Cast<AMyGameState>(World->GetGameState()))
	{
		MyGameState->StartTVMediaCountDown();
	}
	
	
}

void UMyLevelSequenceDirector::InitSceneChange()
{
	UWorld* World = GetWorld();

	if (!World)
	{
		UE_LOG(LogTemp, Warning, TEXT("World was nullptr!"));
		return;
	}

	// Get level stream handler and then load level with callbackfunction to gamestate's unloadinitiallevel
	ALevelStreamHandler* LevelStreamHandler = Cast<ALevelStreamHandler>(UGameplayStatics::GetActorOfClass(World, ALevelStreamHandler::StaticClass()));

	if (!LevelStreamHandler)
	{
		UE_LOG(LogTemp, Warning, TEXT("LevelStreamHandler was nullptr!, forgot to add to world?"));
		return;
	}
	
	LevelStreamHandler->LoadLevel(ELevels::RealRoom, Cast<AMyGameState>(World->GetGameState()), "UnloadInitialLevel");

}

void UMyLevelSequenceDirector::EnterXPScene()
{
	UWorld* World = GetWorld();

	if (!World)
	{
		UE_LOG(LogTemp, Warning, TEXT("World was nullptr!"));
		return;
	}

	//Stop the cinematic so setview works
	if (Player)
	{
		Player->Stop();
	}
	

	// Get level stream handler and then load level with callbackfunction to gamestate's UnloadRealRoomLevel
	ALevelStreamHandler* LevelStreamHandler = Cast<ALevelStreamHandler>(UGameplayStatics::GetActorOfClass(World, ALevelStreamHandler::StaticClass()));

	if (!LevelStreamHandler)
	{
		UE_LOG(LogTemp, Warning, TEXT("LevelStreamHandler was nullptr!, forgot to add to world?"));
		return;
	}
	
	// Change level
	LevelStreamHandler->LoadLevel(ELevels::Game, Cast<AMyGameState>(World->GetGameState()), "UnloadRealRoomLevel");

}


