// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameMode/Clicker2GameMode.h"

#include "ItemSystem/Item.h"
#include "ItemSystem/ItemActor.h"
#include "Player/Clicker2PlayerController.h"
#include "UI/GameHUD.h"
#include "UObject/ConstructorHelpers.h"

AClicker2GameMode::AClicker2GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AClicker2PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(
		TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(
		TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if (PlayerControllerBPClass.Class != nullptr)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<AGameHUD> GameHUDBPClass(TEXT("/Game/TopDown/Blueprints/BP_GameHUD"));
	if (GameHUDBPClass.Class != nullptr)
	{
		HUDClass = GameHUDBPClass.Class;
	}
	else
	{
		HUDClass = AGameHUD::StaticClass();
	}
}

AItemActor* AClicker2GameMode::SpawnItem(UItem* Item, AActor* spawner)
{
	FActorSpawnParameters params;
	return SpawnItem(Item ,spawner->GetTransform().GetLocation(), FRotator::ZeroRotator, params);
}

AItemActor* AClicker2GameMode::SpawnItem(UItem* Item, FVector position, FRotator rotation,FActorSpawnParameters params)
{
	auto item = GetWorld()->SpawnActor<AItemActor>(position,rotation,params);
	item->Setup(Item);
	return item;
}

UItem* AClicker2GameMode::SpawnItem(UItemData* Item)
{
	auto item = NewObject<UItem>();
	item->Setup(Item);
	return item;
}
