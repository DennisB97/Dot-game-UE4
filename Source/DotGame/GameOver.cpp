// Copyright Dennis Bäckström (C) 2021


#include "GameOver.h"
#include "CineCameraComponent.h"
#include "MyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameInstance.h"
#include "UIHandler.h"
#include "GameOverUI.h"
#include "LevelStreamHandler.h"

AGameOver::AGameOver()
{
	PrimaryActorTick.bCanEverTick = false;

	Camera = CreateDefaultSubobject<UCineCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);


}

void AGameOver::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();

	if (!World)
	{
		UE_LOG(LogTemp, Warning, TEXT("World was nullptr!"));
		return;
	}

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);

	// Change camera view to this actor's camera
	if (PlayerController)
	{
		PlayerController->SetViewTargetWithBlend(this, 0.0f, VTBlend_Linear, 0.0, false);
	}
	


	
	// Get the UIHandler
	UIHandler = Cast<AUIHandler>(UGameplayStatics::GetActorOfClass(World, AUIHandler::StaticClass()));


	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());

	LevelStreamHandler = Cast<ALevelStreamHandler>(UGameplayStatics::GetActorOfClass(World, ALevelStreamHandler::StaticClass()));


	if (!GameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("Gameinstance was nullptr!"));
		return;
	}

	if (!UIHandler)
	{
		UE_LOG(LogTemp, Warning, TEXT("UIHandler was nullptr!"));
		return;
	}

	if (!LevelStreamHandler)
	{
		UE_LOG(LogTemp, Warning, TEXT("LevelStreamHandler was nullptr!"));
		return;
	}

	// Updates the gameproperties to UI from gameinstance
	UIHandler->GetGameOverUI()->SetGameProperties();

	// Set UI visible
	UIHandler->SetVisible(true, EUIType::GameOver);

	// Get the score for the ui from gameinstance
	UIHandler->GetGameOverUI()->SetScore(GameInstance->GetScore());

	// Bind level load to lambda called by timer
	FTimerDelegate Delegate;
	AUIHandler* UIHandlerCopy = UIHandler;
	ALevelStreamHandler* LevelStreamHandlerCopy = LevelStreamHandler;
	Delegate.BindWeakLambda(this,
		[UIHandlerCopy,LevelStreamHandlerCopy,this]()
		{
			// put away the ui
			if (UIHandlerCopy)
			{
				UIHandlerCopy->SetVisible(false, EUIType::GameOver);

				// Save the gameproperties from the UI to gameinstance
				UIHandlerCopy->GetGameOverUI()->SaveGameProperties();
			}
			

			if (LevelStreamHandlerCopy)
			{
				LevelStreamHandlerCopy->LoadLevel(ELevels::Game, this, "UnloadGameOver");
			}
			
		}
	);

	//Timer to change level
	World->GetTimerManager().SetTimer(RestartTimer, Delegate, 5.0f, false);
	
}




void AGameOver::UnloadGameOver()
{

	// Unload this actor's level aka. game over level
	LevelStreamHandler->UnloadLevel(ELevels::GameOver);
	
}

