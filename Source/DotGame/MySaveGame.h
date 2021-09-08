// Copyright Dennis Bäckström (C) 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameStructs.h"
#include "MySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class DOTGAME_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()
public:

	UPROPERTY()
	FUserChangeableGameProperties Properties;

	UPROPERTY()
		FString SaveName;

	UPROPERTY()
		uint32 UserID;



};
