// Copyright Dennis Bäckström (C) 2021


#include "AmbientAudio.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"

AAmbientAudio::AAmbientAudio()
{
	// Disable tick for now
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickEnabled(false);

	// Create the components and set hierarchy
	TheRoot = CreateDefaultSubobject<USceneComponent>(TEXT("TheRoot"));
	SetRootComponent(TheRoot);
	AmbientRain = CreateDefaultSubobject<UAudioComponent>(TEXT("AmbientRain"));
	AmbientRain->SetupAttachment(TheRoot);

	AmbientThunder = CreateDefaultSubobject<UAudioComponent>(TEXT("AmbientThunder"));
	AmbientThunder->SetupAttachment(TheRoot);

	SoundCheckBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SoundCheckBox"));
	SoundCheckBox->SetupAttachment(TheRoot);
	SoundCheckBox->SetGenerateOverlapEvents(true);


}


void AAmbientAudio::BeginPlay()
{
	Super::BeginPlay();
	
	// Bind this class' function to the overlap event
	if (SoundCheckBox)
	{
		SoundCheckBox->OnComponentBeginOverlap.AddDynamic(this, &AAmbientAudio::OnBoxBeginOverlap);
	}
	
}


void AAmbientAudio::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// If collision box has been triggered then can decrease volume
	if (bDecreaseVolume)
	{
		DecreaseVolumeGradually(DeltaTime);
	}


}


void AAmbientAudio::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Enable tick 
	SetActorTickEnabled(true);
	bDecreaseVolume = true;
}


void AAmbientAudio::DecreaseVolumeGradually(float DeltaTime)
{

	// Decrease the ambient rain till set minimum reached
	if (AmbientRain && AmbientRain->VolumeMultiplier > MinRainSoundMultiplier)
	{
		AmbientRain->SetVolumeMultiplier(AmbientRain->VolumeMultiplier - (VolumeDecreaseSpeed * DeltaTime));
	}

	// Decrease the ambient thunder&rain till set minimum reached
	if (AmbientThunder && AmbientThunder->VolumeMultiplier > MinThunderSoundMultiplier)
	{
		AmbientThunder->SetVolumeMultiplier(AmbientThunder->VolumeMultiplier - (VolumeDecreaseSpeed * DeltaTime));
	}

	// Again disables tick for no more using of it when sound levels are at wanted
	if (AmbientThunder && AmbientThunder->VolumeMultiplier <= MinThunderSoundMultiplier && AmbientRain->VolumeMultiplier <= MinRainSoundMultiplier)
	{
		bDecreaseVolume = false;
		SetActorTickEnabled(false);
	}


}
