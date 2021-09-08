// Copyright Dennis Bäckström (C) 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DOTGAME_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	


protected:
	virtual void BeginPlay() override;

	
};
