// Copyright Dennis Bäckström (C) 2021


#include "UIHandler.h"
#include "FadeHandler.h"
#include "GameOverUI.h"
#include "GameUI.h"


AUIHandler::AUIHandler()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AUIHandler::SetVisible(const bool bVisible,const EUIType& UIType)
{
	switch (UIType)
	{
	case EUIType::Fade:
	{
		if (bVisible)
		{
			FadeUI->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}

		else
		{
			FadeUI->SetVisibility(ESlateVisibility::Hidden);
		}
		break;
	}

	case EUIType::Game:
	{
		if (bVisible)
		{
			GameUI->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}

		else
		{
			GameUI->SetVisibility(ESlateVisibility::Hidden);
		}
		break;
	}

	case EUIType::GameOver:
	{
		if (bVisible)
		{
			GameOverUI->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}

		else
		{
			GameOverUI->SetVisibility(ESlateVisibility::Hidden);
		}
		break;
	}



	default:
		break;
	}
}

void AUIHandler::BeginPlay()
{
	Super::BeginPlay();
	
	UWorld* World = GetWorld();

	if (!World)
	{
		UE_LOG(LogTemp, Warning, TEXT("World was nullptr!"));
		return;
	}


	// Load the UI's and set them initially invisible

	// Load gameover UI
	const FStringClassReference GameOverUIRef(TEXT("/Game/Blueprints/BP_GameOverUI.BP_GameOverUI_C"));
	 UClass* GameOverUIClass = GameOverUIRef.TryLoadClass<UUserWidget>();

	GameOverUI = Cast<UGameOverUI>(CreateWidget<UUserWidget>(World, GameOverUIClass));


	if (!GameOverUI)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameOverUI was nullptr!"));
	}

	else
	{
		GameOverUI->AddToViewport();
		GameOverUI->SetVisibility(ESlateVisibility::Hidden);
	}
	

	// Load game UI
	const FStringClassReference GameUIRef(TEXT("/Game/Blueprints/BP_GameUI.BP_GameUI_C"));
	 UClass* GameUIClass = GameUIRef.TryLoadClass<UUserWidget>();

	GameUI = Cast<UGameUI>(CreateWidget<UUserWidget>(World, GameUIClass));



	if (!GameUI)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameUI was nullptr!"));
	}

	else
	{
		GameUI->AddToViewport();
		GameUI->SetVisibility(ESlateVisibility::Hidden);
	}
	

	// load FadeUI class
	const FStringClassReference FadeUIRef(TEXT("/Game/Blueprints/BP_FadeHandlerUI.BP_FadeHandlerUI_C"));
	UClass* FadeUIClass = FadeUIRef.TryLoadClass<UUserWidget>();

	
	FadeUI = Cast<UFadeHandler>(CreateWidget<UUserWidget>(World, FadeUIClass));


	if (!FadeUI)
	{
		UE_LOG(LogTemp, Warning, TEXT("FadeUI was nullptr!"));
	}

	else
	{
		FadeUI->AddToViewport();
		FadeUI->SetVisibility(ESlateVisibility::Hidden);
	}
	


}
