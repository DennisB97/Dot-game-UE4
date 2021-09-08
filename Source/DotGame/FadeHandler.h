// Copyright Dennis Bäckström (C) 2021

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FadeHandler.generated.h"

/**
 * Base class for the widget that handles fading in and out, has communcation functions with blueprint version
 */
UCLASS()
class DOTGAME_API UFadeHandler : public UUserWidget
{
	GENERATED_BODY()
public:
	

	/**
	* Calls the blueprint function FadeIn that start animation for fading screen to black
	*/
	UFUNCTION(BlueprintImplementableEvent)
		void FadeIn();

	/**
	* Calls the blueprint function Fadeout that start animation for fading out from the black screen
	*/
	UFUNCTION(BlueprintImplementableEvent)
		void FadeOut();

	
private:



};
