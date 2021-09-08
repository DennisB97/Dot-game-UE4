// Copyright Dennis Bäckström (C) 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStart.generated.h"


/**
* Class responsible of starting the scene in the first level, exists in entry level, and starts only if that level gets loaded
*/
UCLASS()
class DOTGAME_API AGameStart : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameStart();

protected:
	virtual void BeginPlay() override;

	/**
	* This camera will be set as the player's view on beginplay
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BlueprintProtected))
		class UCineCameraComponent* Camera = nullptr;


private:

	/**
	* Pointer to the UIhandler so can run an animation to make scene visible because the UI will be initally black
	*/
	UPROPERTY()
	class AUIHandler* UIHandler = nullptr;

	/**
	* handle for the initial 5 second wait time before cinematic start
	*/
	UPROPERTY()
	FTimerHandle StartTimer;


};
