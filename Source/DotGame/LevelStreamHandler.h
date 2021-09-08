// Copyright Dennis Bäckström (C) 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelStreamHandler.generated.h"

UENUM()
enum class ELevels {

	Entry,
	RealRoom,
	Game,
	GameOver,
};





/**
* This class handles level streaming calls and provides optional callback function
*/
UCLASS()
class DOTGAME_API ALevelStreamHandler : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALevelStreamHandler();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:


	/**
	* This functions call level streaming function, an optional pointer to a class and a function name given then a latentaction will be added for it
	* @param LevelToLoad is the level to be loaded
	* @param ClassP is the pointer to the class which function wants to be called
	* @param CallBackFunctionName is the function name that wants to be called in the _ClassP class after level load
	*/
	void LoadLevel(const ELevels& LevelToLoad, UObject* ClassP = nullptr, const FName CallBackFunctionName = "");



	/**
	* This functions call level streaming function, an optional pointer to a class and a function name given then a latentaction will be added for it
	* @param LevelToDeLoad is the level to be unloaded
	* @param ClassP is the pointer to the class which function wants to be called
	* @param CallBackFunctionName is the function name that wants to be called in the _ClassP class after unload
	*/
	void UnloadLevel(const ELevels& LevelToDeLoad, UObject* ClassP = nullptr, const FName CallBackFunctionName = "");



private:


	const FName EntryLevel = "L_Entry";


	const FName RealRoomLevel = "L_RealRoom";


	const FName GameLevel = "L_GameWorld";


	const FName GameOverLevel = "L_GameOver";


	static int32 LinkageID;


};
