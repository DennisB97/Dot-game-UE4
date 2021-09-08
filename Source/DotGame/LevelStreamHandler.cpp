// Copyright Dennis Bäckström (C) 2021


#include "LevelStreamHandler.h"
#include "kismet/GameplayStatics.h"

int32 ALevelStreamHandler::LinkageID = 0;

ALevelStreamHandler::ALevelStreamHandler()
{
	PrimaryActorTick.bCanEverTick = false;


}

void ALevelStreamHandler::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALevelStreamHandler::LoadLevel(const ELevels& LevelToLoad, UObject* ClassP /*= nullptr*/, const FName CallBackFunctionName /*= ""*/)
{
	FLatentActionInfo LatentAction;

	// If Pointer to a class was provided setup callbackfunction
	if (ClassP)
	{
		LatentAction.CallbackTarget = ClassP;
		LatentAction.ExecutionFunction = CallBackFunctionName;
		LatentAction.Linkage = LinkageID;
		LatentAction.UUID = 123;

		++LinkageID;
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Warning, TEXT("World was nullptr!"));
		return;
	}

	switch (LevelToLoad)
	{
	case ELevels::Entry:
	{
		UGameplayStatics::LoadStreamLevel(World, EntryLevel, true, false, LatentAction);
		break;
	}

	case ELevels::Game:
	{
		UGameplayStatics::LoadStreamLevel(World, GameLevel, true, false, LatentAction);
		break;
	}

	case ELevels::GameOver:
	{
		UGameplayStatics::LoadStreamLevel(World, GameOverLevel, true, false, LatentAction);
		break;
	}

	case ELevels::RealRoom:
	{
		UGameplayStatics::LoadStreamLevel(World, RealRoomLevel, true, false, LatentAction);
		break;
	}

	 default:
	{
		break;
	}


	}


}

void ALevelStreamHandler::UnloadLevel(const ELevels& LevelToDeLoad, UObject* ClassP /*= nullptr*/ , const FName CallBackFunctionName /*= ""*/)
{
	FLatentActionInfo LatentAction;

	// If Pointer to a class was provided setup callbackfunction
	if (ClassP != nullptr)
	{
		LatentAction.CallbackTarget = ClassP;
		LatentAction.ExecutionFunction = CallBackFunctionName;
		LatentAction.Linkage = LinkageID;
		LatentAction.UUID = 123;

		++LinkageID;
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Warning, TEXT("World was nullptr!"));
		return;
	}

	switch (LevelToDeLoad)
	{
	case ELevels::Entry:
	{
		UGameplayStatics::UnloadStreamLevel(World,EntryLevel,LatentAction,false);
		break;
	}

	case ELevels::Game:
	{
		UGameplayStatics::UnloadStreamLevel(World, GameLevel, LatentAction, false);
		break;
	}

	case ELevels::GameOver:
	{
		UGameplayStatics::UnloadStreamLevel(World, GameOverLevel, LatentAction, false);
		break;
	}

	case ELevels::RealRoom:
	{
		UGameplayStatics::UnloadStreamLevel(World, RealRoomLevel, LatentAction, false);
		break;
	}

	default:
	{
		break;
	}


	}

}