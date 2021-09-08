// Copyright Dennis Bäckström (C) 2021


#include "MyGameState.h"
#include "TimerManager.h"
#include "LevelSequencePlayer.h"
#include "MovieSceneSequencePlayer.h"
#include "Door.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/GameSession.h"
#include "MyPlayerController.h"
#include "CineCameraActor.h"
#include "CinematicSequence.h"
#include "TV.h"
#include "Engine/DirectionalLight.h"
#include "AGameBoard.h"
#include "LevelStreamHandler.h"



void AMyGameState::SetTVActor(class ATV* InTV)
{
	TV = InTV;
}

void AMyGameState::SetDoorActor(class ADoor* InDoor)
{
	DoorActor = InDoor;
}

void AMyGameState::SetCinematicPlayer(class ACinematicSequence* InCinematicPlayer)
{
	CinematicPlayer = InCinematicPlayer;
}




void AMyGameState::OpenDoor()
{
	if (!DoorActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Door was not received to gamestate!"));
		return;
	}

	DoorActor->SetOpenDoor();

}

void AMyGameState::PlayFirstCinematic()
{
	if (!CinematicPlayer)
	{
		UE_LOG(LogTemp, Warning, TEXT("CinematicPlayer was not received to gamestate!"));
		return;
	}

	CinematicPlayer->PlayEntry();
}


void AMyGameState::StartTVMediaCountDown()
{
	if (!TV)
	{
		UE_LOG(LogTemp, Warning, TEXT("TV was nullptr!"))
			return;
	}


	TV->PlayMedia(EMediaName::CountDown);


}


void AMyGameState::UnloadInitialLevel()
{

	UWorld* World = GetWorld();
	if (!GetWorld())
	{
		UE_LOG(LogTemp, Warning, TEXT("World was nullptr!"));
		return;
	}

	// Play again grainy media and tv break sound
	if (TV)
	{
		TV->PlayAudio();
		TV->PlayMedia();
	}
	

	// Start the second cinematic
	if (CinematicPlayer)
	{
		CinematicPlayer->PlayMid();
	}
	

	// Get the directional light and make it brighter
	ADirectionalLight* DirectionalLight = Cast<ADirectionalLight>(UGameplayStatics::GetActorOfClass(World, ADirectionalLight::StaticClass()));

	if (!DirectionalLight)
	{
		UE_LOG(LogTemp, Warning, TEXT("DirectionalLight was nullptr!"));
	}
	else
	{
		DirectionalLight->SetBrightness(SkyLightBrigthness);
	}


	LevelStreamHandler = Cast<ALevelStreamHandler>(UGameplayStatics::GetActorOfClass(World, ALevelStreamHandler::StaticClass()));
	if (!LevelStreamHandler)
	{
		UE_LOG(LogTemp, Warning, TEXT("LevelStreamHandler was nullptr!"));
		return;
	}

	// Unload level
	LevelStreamHandler->UnloadLevel(ELevels::Entry);
}


void AMyGameState::UnloadRealRoomLevel()
{

	// Destroy the tv and cinematicplayer because they are in persistent level
	if (TV)
	{
		TV->Destroy();
	}
	
	if (CinematicPlayer)
	{
		CinematicPlayer->Destroy();
	}
	
	if (LevelStreamHandler)
	{
		LevelStreamHandler->UnloadLevel(ELevels::RealRoom);
	}
	
}



