// Copyright Dennis Bäckström (C) 2021

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameStructs.h"
#include "MyGameInstance.generated.h"



/**
 * Store some values between game and game over state, (perhaps file saving too)
 */
UCLASS()
class DOTGAME_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:

	virtual void OnStart() override;


	virtual void Shutdown() override;

	/**
	* For updating the score first here to gameinstance, from where UI will update it's values
	*/
	UFUNCTION()
		void SetScore(const int32 NewScore);
	/**
	* Gets the score
	*/
	UFUNCTION()
		const FGameScore& GetScore() const;


	/**
	* For setting the game values that gameinstance has between levels
	* @param GameProperties is the struct holding the game values
	* @param bIsGivingDefault is default false, it is only true when gameboard actor is giving it's default values first time for gameinstance
	*/
	UFUNCTION()
		const bool SetGameProperties(const FUserChangeableGameProperties& InGameProperties,bool bIsGivingDefault = false);
	/**
	* Gets the game properties and it's blueprintcallable so that the gameover UI can get the values
	*/
	UFUNCTION(BlueprintCallable)
		const FUserChangeableGameProperties& GetGameProperties() const;

private:

	UPROPERTY()
	FGameScore Score;

	UPROPERTY()
	FUserChangeableGameProperties GameProperties;

	/**
	* If it is first time the game starts, then gameinstance needs to get default values from the gameboard actor
	*/
	UPROPERTY()
		bool bNeedsGameDefaultValues = true;

	UPROPERTY()
	FString SaveName = "Save";

	UPROPERTY()
	int32 SaveID = 0;


};
