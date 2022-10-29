// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSystem\BasicItemContainer.h"

#include "ItemSystem\EquippedItem.h"
#include "ItemSystem\InventoryComponent.h"
#include "ItemSystem\Item.h"
#include "ItemSystem\ItemDatas\BackpackItemData.h"
#include "Player\Clicker2Character.h"
#include "Player\PlayerStatsComponent.h"

UBasicItemContainer::UBasicItemContainer()
{
}

void UBasicItemContainer::Initialize(AClicker2Character* owner)
{
	Owner = owner;
}

int UBasicItemContainer::GetSize()
{
	return 9999;
}

EItemType UBasicItemContainer::GetHeldItemType()
{
	return EItemType::All;
}

TArray<UItem*> UBasicItemContainer::GetItems()
{
	return ItemsHeld;
}

bool UBasicItemContainer::CanAddItem(UItem* item)
{
	return CanHeldItemType(item->GetItemData()->GetItemType());
}

bool UBasicItemContainer::AddItem(UItem* item)
{
	bool added = false;

	if (CanAddItem(item))
	{
		ItemsHeld.Add(item);
		added = true;
		OnInventoryUpdated.Broadcast(this);
	}

	return added;
}

bool UBasicItemContainer::RemoveItem(UItem* item)
{
	if (ItemsHeld.Remove(item) > 0)
	{
		OnInventoryUpdated.Broadcast(this);
		return true;
	}

	return false;
}

float UBasicItemContainer::GetWeightOfHeldItems()
{
	float weight = 0;

	for (auto item : ItemsHeld)
	{
		weight += item->GetItemData()->GetWeight();
	}

	return weight * Owner->GetStatsComponent()->BackpackWeightMultiplier;
}

FOnInventoryUpdated* UBasicItemContainer::GetOnInventoryUpdated()
{
	return &OnInventoryUpdated;
}
