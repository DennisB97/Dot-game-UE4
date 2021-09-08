// Copyright Dennis Bäckström (C) 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TV.generated.h"


UENUM()
enum class EMediaName
{
	Grainy,
	CountDown,

};




/**
* This class has a tv and tv table mesh and the TV plays media and an audio component
*/
UCLASS()
class DOTGAME_API ATV : public AActor
{
	GENERATED_BODY()
	
public:	
	ATV();

	/**
	* Used to start the media
	* @Param Takes a optional enum as parameter, default grainy so it plays the grainy media
	*/
	UFUNCTION()
	void PlayMedia(EMediaName MediaName = EMediaName::Grainy);

	/**
	* Used to start the audio for break sound
	*/
	UFUNCTION()
	void PlayAudio();



protected:
	virtual void BeginPlay() override;

	/**
	* The component that holds the mesh for the tv itself
	* @warning staticmesh to be set from editor
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (BlueprintProtected))
		UStaticMeshComponent* TV = nullptr;

	/**
	* The component that holds the mesh for the tv table
	* @warning staticmesh to be set from editor
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (BlueprintProtected))
		UStaticMeshComponent* TVTable = nullptr;

	/**
	* the component that can play the media on the tv screen
	* @Warning needs to be set from editor
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (BlueprintProtected))
		class UMediaPlayer* MediaPlayer = nullptr;

	/**
	* The video source for grainy video
	* @Warning needs to be set from editor
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (BlueprintProtected))
		class UMediaSource* GrainyMedia = nullptr;

	/**
	* The video source for countdown video
	* @Warning needs to be set from editor
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (BlueprintProtected))
		class UMediaSource* CountDownMedia = nullptr;

	/**
	* The audio played when transitioning scene from the tv
	* @Warning audio file needs to be set from editor
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (BlueprintProtected))
		class UAudioComponent* BreakAudio = nullptr;


private:

	UPROPERTY()
	USceneComponent* TheRoot = nullptr;


};
