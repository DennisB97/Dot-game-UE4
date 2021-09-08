// Copyright Dennis Bäckström (C) 2021


#include "GameStart.h"
#include "CineCameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FadeHandler.h"
#include "UObject/SoftObjectPath.h"
#include "MyGameState.h"
#include "UIHandler.h"

AGameStart::AGameStart()
{
	PrimaryActorTick.bCanEverTick = false;


	Camera = CreateDefaultSubobject<UCineCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AGameStart::BeginPlay()
{
	Super::BeginPlay();
	
	UWorld* World = GetWorld();

	if (!World)
	{
		UE_LOG(LogTemp, Warning, TEXT("World was nullptr!"));
		return;
	}

	APlayerController* Controller = UGameplayStatics::GetPlayerController(World,0);

	// Set this actor's camera to be the view
	if (Controller)
	{
		Controller->SetViewTargetWithBlend(this, 0.0f, VTBlend_Linear, 0.0, false);
	}
	
	
	UIHandler = Cast<AUIHandler>(UGameplayStatics::GetActorOfClass(World, AUIHandler::StaticClass()));

	if (!UIHandler)
	{
		UE_LOG(LogTemp, Warning, TEXT("UIHandler was nullptr!"));
		return;
	}


	UIHandler->SetVisible(true, EUIType::Fade);

	// Initially black, so now play animation to make player see
	UIHandler->GetFadeUI()->FadeOut();
	
	// Makes a delegate bound to the timer that will start cinematic and open door after 5 seconds
	FTimerDelegate Delegate;
	AUIHandler* UIHandlerCopy = UIHandler;
	Delegate.BindWeakLambda(this,
		[UIHandlerCopy,World]()
		{
			//Hide the UI
			if (UIHandlerCopy)
			{
				UIHandlerCopy->SetVisible(false, EUIType::Fade);
			}
			
			if (World)
			{
				if (AMyGameState* GameState = Cast<AMyGameState>(World->GetGameState()))
				{
					GameState->OpenDoor();
					GameState->PlayFirstCinematic();
				}
			}
			

		}
	);

	World->GetTimerManager().SetTimer(StartTimer, Delegate, 5.0f,0.0f);
}

