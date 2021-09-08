// Copyright Dennis Bäckström (C) 2021

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameStructs.h"
#include "GameOverUI.generated.h"


/**
 * This is the Game over UI that will be visible when it transitions to game over
 * Will get gameproperties from gameinstance and save properties back to gameinstance
 */
UCLASS()
class DOTGAME_API UGameOverUI : public UUserWidget
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;


	/**
	* blueprint event when called updates the score of the UI
	*/
	UFUNCTION(BlueprintImplementableEvent)
		void SetScore(const FGameScore& Score);
	/**
	* blueprint event when called updates the game properties of the sliders and values
	*/
	UFUNCTION(BlueprintImplementableEvent)
		void SetGameProperties();

	/**
	* This will be called just before the game over level transitions back to level
	* So that the gameproperties are saved to the game instance so game level can access them
	*/
	UFUNCTION()
		void SaveGameProperties();

protected:

	UPROPERTY(BlueprintReadWrite,EditAnywhere, meta = (BlueprintProtected))
	FUserChangeableGameProperties GameProperties;

private:
	class UMyGameInstance* GameInstance = nullptr;

	


};
