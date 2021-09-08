// Copyright Dennis Bäckström (C) 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameOver.generated.h"


/**
* This class exists on the last level which is gameover level, it has a camera that gets the view on begin play
*/
UCLASS()
class DOTGAME_API AGameOver : public AActor
{
	GENERATED_BODY()
	
public:	

	AGameOver();

protected:
	virtual void BeginPlay() override;

	/**
	* This camera will be the main view for the player, one event beginplay to be set to view
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BlueprintProtected))
		class UCineCameraComponent* Camera = nullptr;

public:	
	
	
	/**
	* Will be callback function on level stream load, this calls to unload current level
	*/
	UFUNCTION(BlueprintCallable, Category = "Custom")
		void UnloadGameOver();

private:


	/**
	* Handle for the timer that will call function to change back to game level
	*/
	UPROPERTY()
	FTimerHandle RestartTimer;

	/**
	* Pointer to the UIhandler so can show the gameover UI
	*/
	UPROPERTY()
	class AUIHandler* UIHandler = nullptr;

	/**
	* Pointer to the LevelStreamHandler so levels easy load and unload
	*/
	UPROPERTY()
		class ALevelStreamHandler* LevelStreamHandler = nullptr;


};
