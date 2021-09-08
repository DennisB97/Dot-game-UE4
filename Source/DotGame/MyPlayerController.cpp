// Copyright Dennis Bäckström (C) 2021


#include "MyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "CineCameraActor.h"
#include "AGameBoard.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	

	bEnableMouseOverEvents = true;
	

}


