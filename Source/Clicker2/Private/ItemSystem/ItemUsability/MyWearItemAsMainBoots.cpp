// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSystem\ItemUsability\MyWearItemAsMainBoots.h"

#include "ItemSystem\InventoryComponent.h"
#include "Player\Clicker2Character.h"

UEquippedItem* UMyWearItemAsMainBoots::GetMainHolder(AClicker2Character* User)
{
	return User->GetInventoryComponent()->GetBoots();
}
