// Copyright Dennis Bäckström (C) 2021

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameUI.generated.h"

/**
 *  This is the class for the UI that is visible while the game itself is on
 */
UCLASS()
class DOTGAME_API UGameUI : public UUserWidget
{
	GENERATED_BODY()
public:


	/**
	* This is a blueprint event that gets called when player gets a score and the widget updates it
	*/
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateScore(const bool bGreen);

	/**
	* This is blueprint event that gets called to clear the coin images from the UI
	*/
	UFUNCTION(BlueprintImplementableEvent)
	void ClearImages();
};
