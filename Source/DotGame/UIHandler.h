// Copyright Dennis Bäckström (C) 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UIHandler.generated.h"



/**
* The different UI's that this handles
*/
UENUM()
enum class EUIType
{

	Fade,
	Game,
	GameOver,

};




/**
* This class handles all the game's UI classes
*/
UCLASS()
class DOTGAME_API AUIHandler : public AActor
{
	GENERATED_BODY()

public:
	AUIHandler();


	/**
	* Sets one of the UI's either visible or hidden
	* @param bVisible is the bool for visible or non visible
	* @param UIType is the enum for which UI is set to be hidden/visible
	*/
	UFUNCTION()
		void SetVisible(const bool bVisible, const EUIType& UIType);

	/**
	* Get the FadeUI
	*/
	UFUNCTION()
		class UFadeHandler* GetFadeUI() { return FadeUI; }

	/**
	* Get the GameOverUI
	*/
	UFUNCTION()
		class UGameOverUI* GetGameOverUI() { return GameOverUI; }
	/**
	* Get the GameUI
	*/
	UFUNCTION()
		class UGameUI* GetGameUI() { return GameUI; }

protected:
	virtual void BeginPlay() override;



private:

	UPROPERTY()
		class UFadeHandler* FadeUI = nullptr;

	UPROPERTY()
		class UGameUI* GameUI = nullptr;

	UPROPERTY()
		class UGameOverUI* GameOverUI = nullptr;


};
