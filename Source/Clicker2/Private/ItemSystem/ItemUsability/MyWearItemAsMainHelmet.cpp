// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSystem\ItemUsability\MyWearItemAsMainHelmet.h"
#include "ItemSystem\InventoryComponent.h"
#include "Player\Clicker2Character.h"

UEquippedItem* UMyWearItemAsMainHelmet::GetItemDestination(AClicker2Character* User)
{
	return User->GetInventoryComponent()->GetHelmetPlace();
}
