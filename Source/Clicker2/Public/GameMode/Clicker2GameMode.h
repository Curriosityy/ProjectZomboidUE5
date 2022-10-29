// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework\GameModeBase.h"
#include "Clicker2GameMode.generated.h"

class UItemData;
class UItem;
class AItemActor;
UCLASS(minimalapi)
class AClicker2GameMode : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(Transient, NonTransactional)
	TObjectPtr<UMaterialInstanceDynamic> AimOverlayMaterial;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMaterialParameterCollection> FoSCollection;

public:
	AClicker2GameMode();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	AItemActor* SpawnItem(UItem* Item, AActor* spawner);

	AItemActor* SpawnItem(UItem* Item, FVector position, FRotator rotation, FActorSpawnParameters params);

	UItem* SpawnItem(UItemData* Item);

	void SetAimPostProcessingOverlayValue(float Value);

	inline static const FName LEFT_HAND_WEAPON_SOCKET = "LeftHandWeapon";
	inline static const FName RIGHT_HAND_WEAPON_SOCKET = "RightHandWeapon";
};
