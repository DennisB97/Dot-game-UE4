#pragma once
#include "GameStructs.generated.h"

USTRUCT(Blueprintable)
struct FGameScore
{
	GENERATED_BODY()


		/**
		*  Variable for keeping current score of player
		*/
		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 CurrentScore = 0;

	/**
	*  Variable for keeping previous score of player
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 PreviousScore = 0;
};


/**
* This struct stores properties about the game that can be changed on game over screen
*/
USTRUCT(Blueprintable)
struct FUserChangeableGameProperties
{
	GENERATED_BODY()


		/**
		* The size of the grid where coins spawn
		*/
		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 GridSize = 0;


	/**
	* If should reset the skipped/missed klicks on a correct hit
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bResetMissedClicks = false;


	/**
	* The number coins needed for to get to game over scene
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 RequiredScore = 0;

	/**
	* The amount of skips allowed before game over
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 MaxAllowedSkips = 0;


};
