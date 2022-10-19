// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/EquipmentUserWidget.h"

#include "ItemSystem/EquippedItem.h"
#include "ItemSystem/InventoryComponent.h"
#include "UI/ItemWidget.h"

void UEquipmentUserWidget::Unsubscribe(UInventoryComponent* InventoryComponent)
{
}

void UEquipmentUserWidget::Subscribe(UInventoryComponent* InventoryComponent)
{
}


void UEquipmentUserWidget::Setup(UInventoryComponent* InventoryComponent)
{
	if(CurrentInventoryComponent)
		Unsubscribe(CurrentInventoryComponent);
	
	CurrentInventoryComponent = InventoryComponent;
	Subscribe(CurrentInventoryComponent);
	
	Head->SetItem(InventoryComponent->GetHelmetPlace());
	Backpack->SetItem(InventoryComponent->GetBackpack());
	RightHand->SetItem(InventoryComponent->GetRightHand());
	LeftHand->SetItem(InventoryComponent->GetLeftHand());
	Chest->SetItem(InventoryComponent->GetArmorPlace());
	Legs->SetItem(InventoryComponent->GetLegs());
	Boots->SetItem(InventoryComponent->GetBoots());
}

void UEquipmentUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	Head->Init(0);
	Backpack->Init(0);
	RightHand->Init(0);
	LeftHand->Init(0);
	Chest->Init(0);
	Legs->Init(0);
	Boots->Init(0);
}
