// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSystem\ItemUsability\WearItemAsMainWeapon.h"
#include "ItemSystem\InventoryComponent.h"
#include "Player\Clicker2Character.h"

UEquippedItem* UWearItemAsMainWeapon::GetMainHolder(AClicker2Character* User)
{
	return User->GetInventoryComponent()->GetRightHand();
}
