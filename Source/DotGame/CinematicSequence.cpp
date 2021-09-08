// Copyright Dennis Bäckström (C) 2021


#include "CinematicSequence.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"
#include "MyGameState.h"

ACinematicSequence::ACinematicSequence()
{
	PrimaryActorTick.bCanEverTick = false;


	TheRoot = CreateDefaultSubobject<USceneComponent>(TEXT("TheRoot"));
	SetRootComponent(TheRoot);
	

}

void ACinematicSequence::BeginPlay()
{
	Super::BeginPlay();
	

	UWorld* World = GetWorld();

	if (!World)
	{
		UE_LOG(LogTemp, Warning, TEXT("World was nullptr!"));
		return;
	}

	if (!EntryLevelSequence)
	{
		UE_LOG(LogTemp, Warning, TEXT("LevelSequence was not assigned from the editor!"));
		return;
	}

	// Create the Sequenceplayer and sequenceactor
	FMovieSceneSequencePlaybackSettings Settings{};
	EntrySequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(World, EntryLevelSequence, Settings, SequenceActor);
	
	if (!EntrySequencePlayer)
	{
		UE_LOG(LogTemp, Warning, TEXT("The Created Sequence player was nullptr!"));
	}

	AMyGameState* GameState = Cast<AMyGameState>(World->GetGameState());

	if (!GameState)
	{
		UE_LOG(LogTemp, Warning, TEXT("Gamestate was nullptr!, forgot to set mygamestate?"));
		return;
	}

	// Gives pointer of this actor to gamestate
	GameState->SetCinematicPlayer(this);
	

}



void ACinematicSequence::PlayEntry()
{
	// Plays the first cinematic
	if (SequenceActor)
	{
		SequenceActor->SetSequence(EntryLevelSequence);
		if (SequenceActor->SequencePlayer)
		{
			SequenceActor->SequencePlayer->Play();
		}
		
	}
	
}

void ACinematicSequence::PlayMid()
{

	// Stops the ongoing cinematic and start the next one
	if (!SequenceActor || !SequenceActor->SequencePlayer)
	{
		return;
	}

	SequenceActor->SequencePlayer->Stop();
	
	if (!MidLevelSequence)
	{
		UE_LOG(LogTemp, Warning, TEXT("MidLevelSequence hasn't been assigned from editor!"));
		return;
	}


	SequenceActor->SetSequence(MidLevelSequence);

	SequenceActor->SequencePlayer->Play();

}

void ACinematicSequence::Stop()
{
	if (SequenceActor && SequenceActor->SequencePlayer)
	{
		SequenceActor->SequencePlayer->Stop();
	}
	
}

