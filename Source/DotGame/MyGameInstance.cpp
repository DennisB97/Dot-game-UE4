// Copyright Dennis Bäckström (C) 2021


#include "MyGameInstance.h"
#include "MySaveGame.h"
#include "Kismet/GameplayStatics.h"

void UMyGameInstance::OnStart()
{

	UMySaveGame* LoadedGame = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(SaveName, SaveID));

	if (!LoadedGame)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load save file!"));
		return;
	}


	GameProperties = LoadedGame->Properties;
	// Save file found no need for default values from gameboard actor
	bNeedsGameDefaultValues = false;



}

void UMyGameInstance::Shutdown()
{
	// If exits before the gameboard actor has had chance to give default values don't save
	if (bNeedsGameDefaultValues)
	{
		return;
	}

	UMySaveGame* SaveInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	if (!SaveInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("Creating save game object failed!"));
		return;
	}


	SaveInstance->Properties = GameProperties;

	if (UGameplayStatics::SaveGameToSlot(SaveInstance, SaveName, SaveID) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to save!"));
	}


}

void UMyGameInstance::SetScore(const int32 NewScore)
{
	Score.PreviousScore = Score.CurrentScore;
	Score.CurrentScore = NewScore;
}

const bool UMyGameInstance::SetGameProperties(const FUserChangeableGameProperties& InGameProperties, bool bIsGivingDefault /*= false*/)
{
	if (!bNeedsGameDefaultValues && bIsGivingDefault)
	{
		return false;
	}

	bNeedsGameDefaultValues = false;
	GameProperties.GridSize = InGameProperties.GridSize;
	GameProperties.RequiredScore = InGameProperties.RequiredScore;
	GameProperties.MaxAllowedSkips = InGameProperties.MaxAllowedSkips;
	GameProperties.bResetMissedClicks = InGameProperties.bResetMissedClicks;
	return true;
}

const FUserChangeableGameProperties& UMyGameInstance::GetGameProperties() const
{
	return GameProperties;
}

const FGameScore& UMyGameInstance::GetScore() const
{
	return Score;
}
