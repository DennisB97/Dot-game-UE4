// Copyright Dennis Bäckström (C) 2021


#include "AGameBoard.h"
#include "CineCameraComponent.h"
#include "MyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstance.h"
#include "Math/UnrealMathUtility.h"
#include "CoinHolder.h"
#include "Engine/World.h"
#include "UIHandler.h"
#include "GameUI.h"
#include "LevelStreamHandler.h"
#include "MyGameInstance.h"

AGameBoard::AGameBoard()
{
	PrimaryActorTick.bCanEverTick = true;


	TheRoot = CreateDefaultSubobject<USceneComponent>(TEXT("TheRoot"));
	SetRootComponent(TheRoot);


	Camera = CreateDefaultSubobject<UCineCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(TheRoot);

	StartPointHelper = CreateDefaultSubobject<USceneComponent>(TEXT("StartPointHelper"));
	StartPointHelper->SetupAttachment(TheRoot);


	CoinCmp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CoinCmp"));
	CoinCmp->SetupAttachment(StartPointHelper);



}

void AGameBoard::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Warning, TEXT("World was nullptr!"));
		return;
	}

	GameInstance = Cast<UMyGameInstance>(World->GetGameInstance());

	if (!GameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("Gameinstance was nullptr!, own game instance not set?"));
		return;
	}

	// Send the default game properties to gameinstance, accepts them only if it is first time
	if (GameInstance->SetGameProperties(GameProperties, true) == false)
	{
		// Gameinstance has user set properties get them instead
		GameProperties = GameInstance->GetGameProperties();

	}

	// Scale the camera now when updated the gameproperties above
	ScaleCameraDistance();

	PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(World, 0));

	if (!PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("Playercontroller was nullptr, simulating?"));
	}

	else
	{
		// Set view this camera and show mouse cursor and bind mousebutton events to this actor's functions
		PlayerController->SetViewTargetWithBlend(this, 0.0f, VTBlend_Linear, 0.0, false);
		PlayerController->bShowMouseCursor = true;

		EnableInput(PlayerController);

		if (InputComponent)
		{
			InputComponent->BindAction("TryRedCoinClick", EInputEvent::IE_Pressed, this, &AGameBoard::HandleRedClick);
			InputComponent->BindAction("TryGreenCoinClick", EInputEvent::IE_Pressed, this, &AGameBoard::HandleGreenClick);
		}
		
	}

	UIHandler = Cast<AUIHandler>(UGameplayStatics::GetActorOfClass(World, AUIHandler::StaticClass()));

	if (!UIHandler)
	{
		UE_LOG(LogTemp, Warning, TEXT("UIHandler was nullptr!"));
	}

	else
	{
		UIHandler->SetVisible(true, EUIType::Game);
	}
	


	LevelStreamHandler = Cast<ALevelStreamHandler>(UGameplayStatics::GetActorOfClass(World, ALevelStreamHandler::StaticClass()));
	if (!LevelStreamHandler)
	{
		UE_LOG(LogTemp, Warning, TEXT("LevelStreamHandler was nullptr!"));
	}


	// Set the coin for now out of sight
	if (CoinCmp)
	{
		CoinCmp->SetWorldLocation(FVector(0, 0, 0));
	}
	

	CreateGrid();
}

// Called every frame
void AGameBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (bAdjustCameraFocusAtBegin)
	{
		AdjustCameraFocusAtBegin(DeltaTime);
	}

}



void AGameBoard::HandleGreenClick()
{
	if (HoveredCoinHolder)
	{
		CoinClick(true);
	}

}

void AGameBoard::HandleRedClick()
{
	if (HoveredCoinHolder)
	{
		CoinClick(false);
	}

}


void AGameBoard::CoinClick(const bool bGreenClick)
{
	if (HoveredCoinHolder && CoinCmp && CurrentCoinHolder && UIHandler)
	{

		if (!HoveredCoinHolder->HasCoin())
		{
			// No coin do nothing
			return;
		}

		else
		{
			// Move the coin out of sight
			CoinCmp->SetWorldLocation(FVector(0, 0, 0));
			CurrentCoinHolder->RemoveCoin();

			// Has a coin check if correct mousebutton clicked
			if (HoveredCoinHolder->CheckIfCorrectCoin(bGreenClick))
			{
				// Set that player did not miss this coin spawn
				bClickedOnCoin = true;
				++GameScore.CurrentScore;

				if (UIHandler->GetGameUI())
				{
					UIHandler->GetGameUI()->UpdateScore(bGreenClick);
				}

				if (GameScore.CurrentScore >= GameProperties.RequiredScore)
				{
					SetGameOver();
				}



			}


			// Game over wrong mouse button clicked
			else
			{
				SetGameOver();
			}
		}




	}


}



void AGameBoard::UnloadGameWorld()
{
	LevelStreamHandler->UnloadLevel(ELevels::Game);
}

void AGameBoard::SetGameOver()
{
	if (PlayerController)
	{
		PlayerController->DisableInput(PlayerController);
	}
	

	if (GameInstance)
	{
		GameInstance->SetScore(GameScore.CurrentScore);
	}
	

	if (UIHandler)
	{
		//Hide UI and reset score images
		UIHandler->GetGameUI()->ClearImages();
		UIHandler->SetVisible(false, EUIType::Game);
	}
	
	if (LevelStreamHandler)
	{
		// Load gameover level and callbackfunction unload this world
		LevelStreamHandler->LoadLevel(ELevels::GameOver, this, "UnloadGameWorld");
	}
	
}

void AGameBoard::ScaleCameraDistance()
{
	if (!Camera)
	{
		return;
	}

	float Normalized = static_cast<float>(GameProperties.GridSize - GridMinSize) / (GridMaxSize - GridMinSize);

	float NewCameraPositionX = FMath::LerpStable(CameraMinimum, CameraMaximum, Normalized);

	Camera->SetRelativeLocation(FVector(NewCameraPositionX, 0, 0));
}

void AGameBoard::SpawnCoin()
{
	// Initially nullptr
	if (CurrentCoinHolder)
	{
		CurrentCoinHolder->RemoveCoin();
	}

	// If coin has been clicked on
	if (bClickedOnCoin)
	{
		bClickedOnCoin = false;
		if (GameProperties.bResetMissedClicks)
		{
			SkippedClicks = 0;
		}
	}

	else
	{
		if (!CurrentCoinHolder)
		{
			// do nothing because this is first time
		}

		else
		{
			// Coin was not clicked on by player so add one to skipped
			++SkippedClicks;

			// Player has skipped more than allowed amount = game over
			if (SkippedClicks > GameProperties.MaxAllowedSkips)
			{
				SetGameOver();
			}
		}
		
	}

	// Get random spot on grid
	CurrentCoinHolder = CoinHolders[FMath::RandRange(0, CoinHolders.Num() - 1)];

	if (!CurrentCoinHolder || !StartPointHelper)
	{
		return;
	}

	

	// Get a random coin rotation 0 ,1 from enum with green and red that has the correct rotation set
	const ECoinRotation CoinRotation = static_cast<ECoinRotation>(FMath::RandRange(0, 1));
	const FQuat NewCoinRotation = CoinRotation == ECoinRotation::Green ? FQuat::MakeFromEuler(FVector(0, 0, GreenCoinRotation)) : FQuat::MakeFromEuler(FVector(0, 0, RedCoinRotation));
	const bool bIsGreen = CoinRotation == ECoinRotation::Green ? true : false;

	CurrentCoinHolder->SpawnCoin(bIsGreen);

	if (CoinCmp)
	{
		CoinCmp->SetRelativeRotation(NewCoinRotation);
	}
	
	// Set the coin location to the random chosen
	CoinCmp->SetRelativeLocation(CurrentCoinHolder->GetTransform().GetRelativeTransform(StartPointHelper->GetComponentTransform()).GetLocation());

}



void AGameBoard::AdjustCameraFocusAtBegin(float DeltaTime)
{

	if (!Camera || !GetWorld())
	{
		return;
	}


	if (Camera->CurrentFocusDistance < ManualFocusDistance)
	{
		Camera->FocusSettings.ManualFocusDistance = Camera->CurrentFocusDistance + (SharpenViewSpeed * DeltaTime);
	}

	else
	{
		bAdjustCameraFocusAtBegin = false;

		// Vision is clear, off to start spawning(moving) the coin to places on the grid
		GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &AGameBoard::SpawnCoin, 2.0f, true, 0.0f);
	}




}



void AGameBoard::CreateGrid()
{
	if (!StartPointHelper || !GetWorld())
	{
		return;
	}

	// Adjust the grid start point to the upper corner of view
	StartPointHelper->SetRelativeLocation(FVector(0, -HorizontalOffset * ((GameProperties.GridSize / 2)), VerticalOffset * ((GameProperties.GridSize / 2))));

	// Reserve space for the entire grid
	CoinHolders.Reserve(GameProperties.GridSize * GameProperties.GridSize);



	// go through the grid and spawn coinholder actors to correct location, also bind cursor events
	for (int32 x = 0; x < GameProperties.GridSize; ++x)
	{
		for (int32 y = 0; y < GameProperties.GridSize; ++y)
		{
			// Set the actors to be part of this actor's level so that they get destroyed when game over level is loaded
			FActorSpawnParameters SpawnParams;
			SpawnParams.OverrideLevel = GetLevel();

			FVector Location = FVector(0, HorizontalOffset * x, -VerticalOffset * y);

			ACoinHolder* CoinHolder = GetWorld()->SpawnActor<ACoinHolder>(ACoinHolder::StaticClass(), SpawnParams);
			if (CoinHolder)
			{
				CoinHolder->AttachToComponent(StartPointHelper, FAttachmentTransformRules::KeepRelativeTransform);
				CoinHolder->SetActorRelativeLocation(Location);
				CoinHolder->OnBeginCursorOver.AddDynamic(this, &AGameBoard::CoinHolderOnBeginMouseOver);
				CoinHolder->OnEndCursorOver.AddDynamic(this, &AGameBoard::CoinHolderEndMouseOver);
				CoinHolders.Add(CoinHolder);
			}
			

		}
	}

}



void AGameBoard::CoinHolderOnBeginMouseOver(AActor* TouchedComponent)
{
	if (ACoinHolder* CoinHolder = Cast<ACoinHolder>(TouchedComponent))
	{
		CoinHolder->SetHighlighted(true);
		HoveredCoinHolder = CoinHolder;
	}
	
}

void AGameBoard::CoinHolderEndMouseOver(AActor* TouchedComponent)
{
	if (ACoinHolder* CoinHolder = Cast<ACoinHolder>(TouchedComponent))
	{
		CoinHolder->SetHighlighted(false);
		HoveredCoinHolder = nullptr;
	}

}
