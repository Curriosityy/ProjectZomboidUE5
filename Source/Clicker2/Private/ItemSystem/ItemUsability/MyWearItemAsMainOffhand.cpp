// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSystem\ItemUsability\MyWearItemAsMainOffhand.h"

#include "ItemSystem\InventoryComponent.h"
#include "Player\Clicker2Character.h"

UEquippedItem* UMyWearItemAsMainOffhand::GetItemDestination(AClicker2Character* User)
{
	return User->GetInventoryComponent()->GetLeftHand();
}
