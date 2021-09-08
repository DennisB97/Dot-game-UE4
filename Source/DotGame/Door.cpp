// Copyright Dennis Bäckström (C) 2021


#include "Door.h"
#include "MyGameState.h"
#include "Components/AudioComponent.h"

ADoor::ADoor()
{
	// Disable tick at start
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickEnabled(false);

	// Create components and set hierarchy
	TheRoot = CreateDefaultSubobject<USceneComponent>(TEXT("TheRoot"));
	SetRootComponent(TheRoot);

	DoorFrameMeshCmp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	DoorFrameMeshCmp->SetupAttachment(TheRoot);

	DoorMeshCmp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	DoorMeshCmp->SetupAttachment(DoorFrameMeshCmp);

	DoorAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("DoorAudio"));
	DoorAudio->SetupAttachment(TheRoot);

	// Disable auto activation of sound at start
	DoorAudio->bAutoActivate = false;

}

void ADoor::BeginPlay()
{
	Super::BeginPlay();
	

	UWorld* World = GetWorld();

	if (!World)
	{
		UE_LOG(LogTemp, Warning, TEXT("World was nullptr!"));
		return;
	}



	// Send pointer of this class to gamestate so it can command to open door when needed
	if (AMyGameState* GameState = Cast<AMyGameState>(World->GetGameState()))
	{
		GameState->SetDoorActor(this);
	}
	
}


void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



	// If the door has been set to open
	if (bOpenDoor)
	{
		OpenDoorGradually(DeltaTime);
	}


}

void ADoor::OpenDoorGradually(float DeltaTime)
{
	if (bOpenClockWise)
	{
		// Rotation has been set as clockwise so it adds positive value to the rotation
		if (DoorMeshCmp->GetRelativeTransform().GetRotation().Euler().Z > MaxDoorOpenAngle)
		{
			DoorMeshCmp->AddRelativeRotation(FQuat::MakeFromEuler(FVector(0, 0, DoorOpenSpeed * DeltaTime)));
		}

		// Opening Done
		else
		{
			SetActorTickEnabled(false);
			bOpenDoor = false;
		}
	}


	else
	{
		// Rotation needs to be negative addition for it to go anticlockwise
		if (DoorMeshCmp->GetRelativeTransform().GetRotation().Euler().Z > MaxDoorOpenAngle)
		{
			DoorMeshCmp->AddRelativeRotation(FQuat::MakeFromEuler(FVector(0, 0, -DoorOpenSpeed * DeltaTime)));
		}

		// Opening Done
		else
		{
			SetActorTickEnabled(false);
			bOpenDoor = false;
		}
	}


}

void ADoor::SetOpenDoor()
{
	// Set door to be opened and start play door's audio
	bOpenDoor = true;
	SetActorTickEnabled(true);
	DoorAudio->Play();
}

