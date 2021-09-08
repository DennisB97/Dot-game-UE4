// Copyright Dennis Bäckström (C) 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"


/**
* This class is responsible for having the door mesh, playing a sound on door opening, and also gradually opening the door by rotating it on tick
*/
UCLASS()
class DOTGAME_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADoor();


	/**
	* Called when the door is set to be opened, sets a bool to true
	*/
	UFUNCTION()
	void SetOpenDoor();


protected:
	virtual void BeginPlay() override;


	/**
	* Frame around the door meshcomponent
	* @warning To be set from editor
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (BlueprintProtected))
		UStaticMeshComponent* DoorFrameMeshCmp = nullptr;

	/**
	* The door meshcomponent
	* @warning This needs to be also set from blueprint and adjusted location of the door to the correct place
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (BlueprintProtected))
		UStaticMeshComponent* DoorMeshCmp = nullptr;

	/**
	* To control how much the door can be opened
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (BlueprintProtected))
		float MaxDoorOpenAngle = 0.0f;

	/**
	*To control how fast the door opens, multiplied speed every tick
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (BlueprintProtected))
		float DoorOpenSpeed = 0.0f;


	/**
	*To control which way door opens
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (BlueprintProtected))
		bool bOpenClockWise = false;

	/**
	* The sound for the door opening
	* @warning Sound needs to be set from editor!
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (BlueprintProtected))
		class UAudioComponent* DoorAudio = nullptr;

	
public:	
	virtual void Tick(float DeltaTime) override;

	

private:

	UPROPERTY()
		USceneComponent* TheRoot = nullptr;

	/**
	* This variable will be set from function when door is suppose to open so the code in tick will run
	*/
	UPROPERTY()
	bool bOpenDoor = false;
	
	/**
	* This is the function that makes the door rotate and open, forwarded from tick
	* @Param Takes the Tick functions DeltaTime as parameter
	*/
	UFUNCTION()
	void OpenDoorGradually(float DeltaTime);




};
