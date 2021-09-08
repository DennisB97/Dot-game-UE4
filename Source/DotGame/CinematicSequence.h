// Copyright Dennis Bäckström (C) 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CinematicSequence.generated.h"



/**
* This class is responsible of holding the two cinematics of this game and playing them
*/
UCLASS()
class DOTGAME_API ACinematicSequence : public AActor
{
	GENERATED_BODY()

public:
	ACinematicSequence();


protected:
	virtual void BeginPlay() override;

public:


	/**
	* This will make it play the first sequence
	*/
	UFUNCTION()
		void PlayEntry();

	/**
	* This will make it play the second sequence
	*/
	UFUNCTION()
		void PlayMid();

	
	UFUNCTION()
	void Stop();

protected:

	/**
	* This will point to the cinematic for the beginning
	  @Warning Needs to be set from editor
	*/
	UPROPERTY(EditAnywhere, meta = (BlueprintProtected))
		class ULevelSequence* EntryLevelSequence = nullptr;

	/**
	* This will point to the second cinematic
	  @Warning Needs to be set from editor
	*/
	UPROPERTY(EditAnywhere, meta = (BlueprintProtected))
		class ULevelSequence* MidLevelSequence = nullptr;



private:

	UPROPERTY()
		USceneComponent* TheRoot = nullptr;


	/**
	* This pointer to the Sequenceactor that will be created from the same function as the variable below
	*/
	UPROPERTY()
		class ALevelSequenceActor* SequenceActor = nullptr;


	/**
	* This pointer to the Sequenceplayer that will be created on beginplay
	*/
	UPROPERTY()
		class ULevelSequencePlayer* EntrySequencePlayer;

};
