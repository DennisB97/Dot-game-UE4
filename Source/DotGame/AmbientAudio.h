// Copyright Dennis Bäckström (C) 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmbientAudio.generated.h"


/**
* This class is responsible of some ambient audio, also has a collision box that activates a volume decrease
*/
UCLASS()
class DOTGAME_API AAmbientAudio : public AActor
{
	GENERATED_BODY()
	
public:	
	AAmbientAudio();

	virtual void Tick(float DeltaTime) override;


	
protected:
	virtual void BeginPlay() override;

public:	
	
	/**
	* For triggering volume decrease when camera overlaps this collision box
	*/
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:

	/**
	* This will be the ambient 2d rain sound that loops
	  @Warning The audio file for this component needs to be set from editor!
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (BlueprintProtected))
		class UAudioComponent* AmbientRain = nullptr;

	/**
	* This will be the ambient thunder
	  @Warning The audio file for this component needs to be set from editor!
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (BlueprintProtected))
		class UAudioComponent* AmbientThunder = nullptr;


	/**
	* Collision box that is responsible of firing lower volume function
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (BlueprintProtected))
		class UBoxComponent* SoundCheckBox = nullptr;


	/**
	* Tweakable how low the sound should be when going inside
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (BlueprintProtected))
		float MinRainSoundMultiplier = 0.65f;

	/**
	* Tweakable how low the sound should be when going inside
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (BlueprintProtected))
		float MinThunderSoundMultiplier = 0.65f;

	/**
	* How much volume would be lowered by every second, this variable * deltatime
	*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (BlueprintProtected))
		float VolumeDecreaseSpeed = 0.15f;



private:

	UPROPERTY()
	USceneComponent* TheRoot = nullptr;

	/**
	* Collision box sets this value when camera overlaps, so that on tick volume can be periodically decreased to wanted level
	*/
	UPROPERTY()
	bool bDecreaseVolume = false;
	
	/**
	* This function that will be called from tick to decrease volume gradually
	* @Param Takes the Tick's deltatime as parameter
	*/
	UFUNCTION()
		void DecreaseVolumeGradually(float DeltaTime);


	
};
