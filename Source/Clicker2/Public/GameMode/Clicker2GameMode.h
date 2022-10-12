// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Clicker2GameMode.generated.h"

class UItemData;
class UItem;
class AItemActor;
UCLASS(minimalapi)
class AClicker2GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AClicker2GameMode();

	AItemActor* SpawnItem(UItem* Item);

	UItem* SpawnItem(UItemData* Item);
};
