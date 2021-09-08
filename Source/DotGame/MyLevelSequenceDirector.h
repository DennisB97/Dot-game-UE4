// Copyright Dennis Bäckström (C) 2021

#pragma once

#include "CoreMinimal.h"
#include "LevelSequenceDirector.h"
#include "MyLevelSequenceDirector.generated.h"

class ALevelStreamHandler;

/**
 * This class gets functions called from the sequence's events
 */
UCLASS()
class DOTGAME_API UMyLevelSequenceDirector : public ULevelSequenceDirector
{
	GENERATED_BODY()
public:


	/**
	* Event called from sequence for changing media
	*/
	UFUNCTION(BlueprintCallable)
	void PlayCountDownMedia();

	/**
	* Event called from sequence for changing first level
	*/
	UFUNCTION(BlueprintCallable)
	void InitSceneChange();

	/**
	* Event called from sequence for changing to the last actual game level
	*/
	UFUNCTION(BlueprintCallable)
		void EnterXPScene();

	
};
