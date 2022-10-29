// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSystem\ItemUsability\WearItemAsMain.h"

#include "ItemSystem\BasicItemContainer.h"
#include "ItemSystem\EquippedItem.h"
#include "ItemSystem\InventoryComponent.h"
#include "Player\Clicker2Character.h"

void UWearItemAsMain::Use(AClicker2Character* User, UItem* Item)
{
	UEquippedItem* mainHolder = GetMainHolder(User);

	if (mainHolder->GetItem() != nullptr && mainHolder != Item->GetHolder())
	{
		User->GetInventoryComponent()->GetHeldItems()->AddItem(mainHolder->GetItem());
	}

	mainHolder->AddItem(Item);
}
