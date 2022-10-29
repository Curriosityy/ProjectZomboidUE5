// Fill out your copyright notice in the Description page of Project Settings.


#include "UI\GameHUD.h"

#include "Blueprint\UserWidget.h"
#include "ItemSystem\BasicItemContainer.h"
#include "ItemSystem\InventoryComponent.h"
#include "ItemSystem\ItemHelper.h"
#include "ItemSystem\SearchForPickupColliderComponent.h"
#include "Player\Clicker2Character.h"
#include "UI\DropItemOnGroundUserWidget.h"
#include "UI\DropItemOnGroundUserWidget.h"
#include "UI\InventoryUserWidget.h"
#include "UI\ItemWidget.h"
#include "UI\ScavengingUserWidget.h"

AGameHUD::AGameHUD()
{
}

void AGameHUD::ShowDropItemOnGroundWidget(AClicker2Character* characterToOpenInventory)
{
	if (!DropItemOnGround)
	{
		DropItemOnGround = CreateWidget<UDropItemOnGroundUserWidget>(GetWorld(), DropItemOnGroundWidget);
		DropItemOnGround->AddToViewport(-1000);
		DropItemOnGround->Setup(characterToOpenInventory);
	}
}

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();
	UItemWidget::sIsDragged = false;
}

void AGameHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AGameHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AGameHUD::OpenInventoryWindow(AClicker2Character* characterToOpenInventory)
{
	ShowDropItemOnGroundWidget(characterToOpenInventory);

	if (Inventory == nullptr)
	{
		Inventory = CreateWidget<UInventoryUserWidget>(GetWorld(), InventoryWidget);

		if (Inventory)
		{
			MouseBlockers.Add(Inventory);
			Inventory->AddToViewport();
			Inventory->Show(characterToOpenInventory);
		}
	}
	else
	{
		Inventory->Show(characterToOpenInventory);
	}
}

void AGameHUD::OpenScavengeWindow(AClicker2Character* characterToOpenInventory)
{
	ShowDropItemOnGroundWidget(characterToOpenInventory);

	if (Scavenge == nullptr)
	{
		Scavenge = CreateWidget<UScavengingUserWidget>(GetWorld(), ScavengeWidget);

		if (Scavenge)
		{
			MouseBlockers.Add(Scavenge);
			Scavenge->AddToViewport();
			Scavenge->Show(characterToOpenInventory->GetSearchItemComponent());
		}
	}
	else
	{
		Scavenge->Show(characterToOpenInventory->GetSearchItemComponent());
	}
}

bool AGameHUD::IsMouseOverBlockUI()
{
	bool mouseOver = false;

	for (auto Element : MouseBlockers)
	{
		mouseOver |= Element->IsMouseOver();
	}

	mouseOver |= UItemWidget::IsDragged();

	return mouseOver;
}

void AGameHUD::MoveItemBetweenInventoryAndScavengeItemHolders(IItemHolder* CurrentItemHolder, UItem* ItemToMove)
{
	auto player = Cast<AClicker2Character>(PlayerOwner->GetPawn());
	bool isCurrentItemHolderInventory = player->GetInventoryComponent()->GetHeldItems() == CurrentItemHolder;

	if (isCurrentItemHolderInventory)
	{
		int index = 0;

		if (Scavenge != nullptr)
		{
			index = Scavenge->GetCurrentScavengingWindow();
		}

		ItemHelper::AddItemToNewHolder(CurrentItemHolder,
		                               player->GetSearchItemComponent()->GetOverlappedItemsContainers()[index],
		                               ItemToMove);
	}
	else
	{
		ItemHelper::AddItemToNewHolder(CurrentItemHolder,
		                               player->GetInventoryComponent()->GetHeldItems(),
		                               ItemToMove);
	}
}
