// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSystem\ItemUsability\WearItemAsMain.h"

#include "ItemSystem\BasicItemContainer.h"
#include "ItemSystem\EquippedItem.h"
#include "ItemSystem\InventoryComponent.h"
#include "ItemSystem\ItemHelper.h"
#include "Player\Clicker2Character.h"

void UWearItemAsMain::Use(AClicker2Character* User, UItem* Item)
{
	UEquippedItem* mainHolder = GetItemDestination(User);

	if (Item->GetHolder() != mainHolder)
	{
		if (mainHolder->GetItem() != nullptr)
		{
			ItemHelper::AddItemToNewHolder(User->GetInventoryComponent()->GetHeldItems(), Item);
		}

		ItemHelper::AddItemToNewHolder(mainHolder, Item);
	}
}
