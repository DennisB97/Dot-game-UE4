// Copyright Dennis Bäckström (C) 2021


#include "GameOverUI.h"
#include "MyGameInstance.h"



void UGameOverUI::NativeConstruct()
{
	Super::NativeConstruct();

	UWorld* World = GetWorld();

	if (!World)
	{
		UE_LOG(LogTemp, Warning, TEXT("World was nullptr!"));
		return;
	}

	GameInstance = Cast<UMyGameInstance>(World->GetGameInstance());

	if (!GameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("Gameinstance was nullptr!"));
	}

}



void UGameOverUI::SaveGameProperties()
{
	GameInstance->SetGameProperties(GameProperties);
}