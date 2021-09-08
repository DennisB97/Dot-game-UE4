// Copyright Dennis Bäckström (C) 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStructs.h"
#include "AGameBoard.generated.h"


// For the coin relative rotation which side is which color
UENUM()
enum ECoinRotation
{
	Red = 0,
	Green = 1,
};




/**
* This class takes care of the "gameboard" where the coinholder actors will be spawned on proper locations in a grid, and also holds the camera that player will use
*/
UCLASS()
class DOTGAME_API AGameBoard : public AActor
{
	GENERATED_BODY()

public:

	AGameBoard();

	virtual void Tick(float DeltaTime) override;



	/**
	* This is a custom function for the mouseover event, essentially for the purpose to make an effect to know which grid is hovered over
	* @param TouchedComponent is the component that got hovered over
	*/
	UFUNCTION()
		void CoinHolderOnBeginMouseOver(AActor* TouchedComponent);
	UFUNCTION()
	void CoinHolderEndMouseOver(AActor* TouchedComponent);




protected:
	virtual void BeginPlay() override;

public:

	
	
protected:

	/**
	* Root of the actor
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (BlueprintProtected))
		USceneComponent* TheRoot = nullptr;


	/**
	* This points to the scenecomponent that is placed as helper where from to generate the grid
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (BlueprintProtected))
		USceneComponent* StartPointHelper = nullptr;


	/**
	* This will be the coin with green and red side, it will be created once and only moved along the grid and away from grid
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (BlueprintProtected))
		USkeletalMeshComponent* CoinCmp = nullptr;


	/**
	* This variable is offset for the horizontal width between the grid center points
	* Length is in mm
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (BlueprintProtected))
		float HorizontalOffset = 20.0f;

	/**
	* This variable is offset for the vertical width between the grid center points
	* Length is in mm
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (BlueprintProtected))
		float VerticalOffset = 20.0f;

	/**
	* This is the minimum distance camera can be from the grid, camera position will be lerped between two values depending on grid size
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (BlueprintProtected))
		float CameraMinimum = -250.0f;

	/**
	* This is the maximum distance camera can be from the grid, camera position will be lerped between two values depending on grid size
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (BlueprintProtected))
		float CameraMaximum = -900.0f;

	/**
	* This camera will be the main view for the player, one event beginplay to be set to view
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BlueprintProtected))
		class UCineCameraComponent* Camera = nullptr;

	/**
	* Camera will initially be blurred, this is the speed how fast it will sharpen up
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (BlueprintProtected))
		float SharpenViewSpeed = 35.0f;

	/**
	* Camera will initially be blurred, this is the focus distance untill it will be sharp enough
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (BlueprintProtected))
		float ManualFocusDistance = 500.0f;


	/**
	* This is the rotation value for the coin to show the red side
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (BlueprintProtected))
		float RedCoinRotation = 0.0f;
	/**
	* This is the rotation value for the coin to show the green side
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (BlueprintProtected))
		float GreenCoinRotation = 180.0f;

	/**
	* Max size of grid
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (BlueprintProtected))
		int32 GridMaxSize = 20;

	/**
	* Min size of grid
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (BlueprintProtected))
		int32 GridMinSize = 4;


	/**
	* Set default values for some properties that user can also change from game over UI
	* Grid size, one way
	* if should reset skipped count on a correct hit
	* Max score needed for game over
	* Max allowed skips
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (BlueprintProtected))
		FUserChangeableGameProperties GameProperties {
		10,
			false,
			10,
			3
	};


private:

	/**
	* This will have all the spawned coinholder actors, which are also the locations of the grid
	*/
	UPROPERTY()
		TArray<class ACoinHolder*> CoinHolders;

	/**
	* This is the bool that disables later the focusing of camera, because camera vision is blurred at start
	*/
	UPROPERTY()
	bool bAdjustCameraFocusAtBegin = true;

	/**
	* If player clicked on the coin correctly
	*/
	UPROPERTY()
		bool bClickedOnCoin = false;


	/**
	* The current amount of skipped clicks
	*/
	UPROPERTY()
	int32 SkippedClicks = 0;
	
	/**
	* How many has been clicked correctly
	*/
	UPROPERTY()
	FGameScore GameScore;

	/**
	* Timerhandle for the timer that makes every 2 second a coin spawn(move to location)
	*/
	UPROPERTY()
	FTimerHandle SpawnTimer;

	/**
	* This functions is called from timer every 2 seconds to move the coin location to one of the grid locations
	*/
	UFUNCTION()
	void SpawnCoin();

	/**
	* This functions is called from tick untill the camera view is not blurred anymore
	*/
	UFUNCTION()
	void AdjustCameraFocusAtBegin(float DeltaTime);
	
	/**
	* This functions takes care of spawning coinholder actors in a grid and binds the required mouse cursor over events
	*/
	UFUNCTION()
	void CreateGrid();

	
	UPROPERTY()
		class AMyPlayerController* PlayerController = nullptr;

	UPROPERTY()
	 class UMyGameInstance* GameInstance = nullptr;


	/**
	* Store the currently hovered coinholder
	*/
	UPROPERTY()
	class ACoinHolder* HoveredCoinHolder = nullptr;

	/**
	* Store the current coinholder that has the coin
	*/
	UPROPERTY()
	class ACoinHolder* CurrentCoinHolder = nullptr;


	/**
	* The right click bound event, checks from coinholder if it clicked on one with a coin
	*/
	UFUNCTION()
		void HandleGreenClick();

	/**
	* The left click bound event, checks from coinholder if it clicked on one with a coin
	*/
	UFUNCTION()
		void HandleRedClick();

	/**
	* Forward the mouse events to this function that forwards to coinholder which checks if clicked on a correct coin
	*/
	UFUNCTION()
		void CoinClick(const bool bGreenClick);


	UPROPERTY()
	class AUIHandler* UIHandler = nullptr;

	UPROPERTY()
	class ALevelStreamHandler* LevelStreamHandler = nullptr;

	

	UFUNCTION()
	void UnloadGameWorld();

	UFUNCTION()
	void SetGameOver();


	/**
	* Function for scaling the camera distance, depending on the chosen size of the grid
	*/
	UFUNCTION()
    void ScaleCameraDistance();
};
