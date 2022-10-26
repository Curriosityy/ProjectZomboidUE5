// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework\HUD.h"
#include "GameHUD.generated.h"

class UDropItemOnGroundUserWidget;
class UScavengingUserWidget;
class AClicker2Character;
class UInventoryUserWidget;
class IMouseBlocker;
class UItemHolderWidget;
class IItemHolder;
class UItem;
/**
 * 
 */
UCLASS()
class CLICKER2_API AGameHUD : public AHUD
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> InventoryWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> ScavengeWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> DropItemOnGroundWidget;

	UPROPERTY(Transient, NonTransactional)
	TObjectPtr<UInventoryUserWidget> Inventory;

	UPROPERTY(Transient, NonTransactional)
	TObjectPtr<UScavengingUserWidget> Scavenge;

	UPROPERTY(Transient, NonTransactional)
	TObjectPtr<UDropItemOnGroundUserWidget> DropItemOnGround;

	TArray<IMouseBlocker*> MouseBlockers;

public:
	AGameHUD();

	void ShowDropItemOnGroundWidget(AClicker2Character* characterToOpenInventory);

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void DrawHUD() override;

	void OpenInventoryWindow(AClicker2Character* characterToOpenInventory);

	void OpenScavengeWindow(AClicker2Character* characterToOpenInventory);

	bool IsMouseOverBlockUI();

	void MoveItemBetweenInventoryAndScavengeItemHolders(IItemHolder* CurrentItemHolder, UItem* ItemToMove);
};
