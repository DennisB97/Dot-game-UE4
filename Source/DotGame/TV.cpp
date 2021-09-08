// Copyright Dennis Bäckström (C) 2021


#include "TV.h"
#include "MediaPlayer.h"
#include "MediaSource.h"
#include "MyGameState.h"
#include "Components/AudioComponent.h"

ATV::ATV()
{
	PrimaryActorTick.bCanEverTick = false;


	TheRoot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TheRoot"));
	SetRootComponent(TheRoot);

	TV = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TV"));
	TV->SetupAttachment(TheRoot);

	TVTable = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TVTable"));
	TVTable->SetupAttachment(TheRoot);

	BreakAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("BreakAudio"));
	BreakAudio->SetupAttachment(TheRoot);

	// Do not play audio on start
	BreakAudio->bAutoActivate = false;

}

void ATV::PlayMedia(EMediaName MediaName /*= EMediaName::Grainy*/)
{





	// Start play the media
	switch (MediaName)
	{
	case EMediaName::Grainy:
	{
		if (!GrainyMedia)
		{
			UE_LOG(LogTemp, Warning, TEXT("GrainyMedia was not set!"));
		}

		else
		{
			MediaPlayer->SetLooping(true);
			MediaPlayer->OpenSource(GrainyMedia);
			MediaPlayer->Play();
		}

		break;
	}

	case EMediaName::CountDown:
	{
		if (!CountDownMedia)
		{
			UE_LOG(LogTemp, Warning, TEXT("CountDownMedia was not set!"));
		}

		else
		{
			MediaPlayer->SetLooping(false);
			MediaPlayer->OpenSource(CountDownMedia);
			MediaPlayer->Play();
		}

		break;
	}

	}




}

void ATV::PlayAudio()
{
	BreakAudio->Play();
}

void ATV::BeginPlay()
{
	Super::BeginPlay();

	if (!MediaPlayer)
	{
		UE_LOG(LogTemp, Warning, TEXT("MediaPlayer has not been set from editor!"));
		return;
	}

	else
	{
		// Play grainy media by default from the begin play
		PlayMedia();
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Warning, TEXT("World was nullptr!"));
		return;
	}


	AMyGameState* GameState = Cast<AMyGameState>(World->GetGameState());
	if (!GameState)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameState was nullptr! MyGamestate not set?"));
		return;
	}

	// Forward a pointer of this to gamestate
	GameState->SetTVActor(this);

}

