// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSystem\ItemHolderActor.h"

#include "ItemSystem\Item.h"

int AItemHolderActor::GetSize()
{
	return 999999;
}

EItemType AItemHolderActor::GetHeldItemType()
{
	return EItemType::All;
}

TArray<UItem*> AItemHolderActor::GetItems()
{
	return HeldItems;
}

bool AItemHolderActor::CanAddItem(UItem* item)
{
	return true;
}

bool AItemHolderActor::AddItem(UItem* item)
{
	HeldItems.Add(item);
	OnInventoryUpdated.Broadcast(this);
	return true;
}

bool AItemHolderActor::RemoveItem(UItem* item)
{
	if (HeldItems.Remove(item) > 0)
	{
		OnInventoryUpdated.Broadcast(this);

		return true;
	}
	return false;
}

float AItemHolderActor::GetWeightOfHeldItems()
{
	return 0;
}

FOnInventoryUpdated* AItemHolderActor::GetOnInventoryUpdated()
{
	return &OnInventoryUpdated;
}

bool AItemHolderActor::CanPickUp()
{
	return false;
}
