// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSystem/EquippedItem.h"

#include "ItemSystem/Item.h"
#include "ItemSystem/ItemDatas/ItemData.h"

void UEquippedItem::Initialize(EItemType itemType)
{
	HeldItemType = itemType;
}

int UEquippedItem::GetSize()
{
	return 1;
}

EItemType UEquippedItem::GetHeldItemType()
{
	return HeldItemType;
}

TArray<UItem*> UEquippedItem::GetItems()
{
	TArray<TObjectPtr<UItem>> items = TArray<TObjectPtr<UItem>>();
	items.Add(Item);
	return items;
}

UItem* UEquippedItem::GetItem()
{
	return Item;
}

bool UEquippedItem::CanAddItem(UItem* item)
{
	return CanHeldItemType(item->GetItemData()->GetItemType()) && Item == nullptr;
}

bool UEquippedItem::AddItem(IItemHolder* previousOwner, UItem* item)
{

	
	if(CanAddItem(item))
	{
		if(previousOwner!=nullptr)
		{
			previousOwner->RemoveItem(item);
		}
		
		Item = item;
		OnEquippedItemUpdated.Broadcast(this);

		return true;
	}
	
	return false;
}

bool UEquippedItem::RemoveItem(UItem* item)
{
	if(Item == item)
	{
		Item = nullptr;
		OnEquippedItemUpdated.Broadcast(this);
		
		return true;
	}
	
	return false;
}

float UEquippedItem::GetWeightOfHeldItems()
{

	return Item == nullptr?0:Item->GetItemData()->GetWeight();
}

FOnInventoryUpdated* UEquippedItem::GetOnInventoryUpdated()
{
	return &OnEquippedItemUpdated;
}
