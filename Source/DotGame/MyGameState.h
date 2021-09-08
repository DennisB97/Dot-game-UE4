// Copyright Dennis Bäckström (C) 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameState.generated.h"



/**
 * This gamestate receives pointers from the actors from world so it calls their functions
 */
UCLASS()
class DOTGAME_API AMyGameState : public AGameStateBase
{
	GENERATED_BODY()
public:


	/**
	* Function that gets the pointer to the door actor in the world, received by the actor itself on begin play
	*/
	UFUNCTION()
		void SetDoorActor(class ADoor* InDoor);

	/**
	* Function that gets the pointer to the sequence actor in the world, received by the actor itself on begin play
	*/
	UFUNCTION()
		void SetCinematicPlayer(class ACinematicSequence* InCinematicPlayer);

	/**
	* Function that gets the pointer to the tv actor in the world, received by the actor itself on begin play
	*/
	UFUNCTION()
		void SetTVActor(class ATV* InTV);



	/**
	* Forwards to door's function so that the door opens
	*/
	UFUNCTION()
	void OpenDoor();

	/**
	* Forwards to cinematic actor so that it starts playing first cinematic
	*/
	UFUNCTION()
	void PlayFirstCinematic();


	/**
	* Forwarded from SequenceDirector origin from sequence event, sets the tv to play next media
	*/
	UFUNCTION()
		void StartTVMediaCountDown();


	/**
	* Callback function for load level stream, unloads the real room level
	*/
	UFUNCTION(BlueprintCallable, Category = "Custom")
		void UnloadRealRoomLevel();

	/**
	* This function is a callback function from load level stream when loading the next level
	*/
	UFUNCTION(BlueprintCallable, Category = "Custom")
		void UnloadInitialLevel();




private:

	/**
	* This will point to the door actor in world, received by the actor itself on begin play
	*/
	UPROPERTY()
		class ADoor* DoorActor = nullptr;

	
	/**
	* This will point to the CinematicSequence that holds the correct sequences to be played
	* received by the actor itself on begin play
	*/
	UPROPERTY()
		class ACinematicSequence* CinematicPlayer = nullptr;


	
	/**
	* This points to the TV actor, will be used to change the media for it
	* Reiceved from the actor itself on begin play
	*/
	UPROPERTY()
		class ATV* TV = nullptr;


	/**
	* The brightness to be set for the directional light before the game level gets started
	*/
	const float SkyLightBrigthness = 2.0f;

	/**
	* Used in this class for unloading levels
	*/
	UPROPERTY()
		class ALevelStreamHandler* LevelStreamHandler = nullptr;

};

