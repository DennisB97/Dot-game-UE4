// Copyright Dennis Bäckström (C) 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoinHolder.generated.h"



/**
* This is the actor that gets spawned on the game grid
* Has functions to add and remove coin
*/
UCLASS()
class DOTGAME_API ACoinHolder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoinHolder();


	/**
	* This function sets the actor to have a coin
	* @param bGreen is the bool for if the coin is either green or a red
	*/
	UFUNCTION()
	void SpawnCoin(const bool bGreen);

	/**
	* This function sets the bhascoin bool to false so that this actor does not have a coin
	*/
	UFUNCTION()
	void RemoveCoin();

	/**
	* This function gets called from the gameboard when mouse is hovered over so that the texture changes
	* @param bNewHighlighted is either on hover or end hovering that the texture changes to default or emissive
	*/
	UFUNCTION()
	void SetHighlighted(const bool bNewHighlighted);

	/**
	* Checks if the click corresponds to this coins color
	*/
	UFUNCTION()
	const bool CheckIfCorrectCoin(const bool bGreenClick) const;

	/**
	* Get if the coin has a coin or not
	*/
	UFUNCTION()
	const bool HasCoin() const;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



private:

	UPROPERTY()
	USkeletalMeshComponent* CoinHolder = nullptr;

	UPROPERTY()
	USkeletalMesh* SkeletalMesh = nullptr;


	/**
	* bool to know if this actor has the coin or not
	*/
	bool bHasCoin = false;

	/**
	* bool to know if the coin is green or red
	*/
	bool bIsGreen = false;

	UPROPERTY()
		UMaterialInstanceDynamic* EmissiveFrameMaterial = nullptr;

};
