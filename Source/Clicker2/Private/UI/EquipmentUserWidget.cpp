// Fill out your copyright notice in the Description page of Project Settings.


#include "UI\EquipmentUserWidget.h"

#include "ItemSystem\EquippedItem.h"
#include "ItemSystem\InventoryComponent.h"
#include "UI\ItemWidget.h"

void UEquipmentUserWidget::Unsubscribe(UInventoryComponent* InventoryComponent)
{
	InventoryComponent->GetHelmetPlace()->GetOnInventoryUpdated()
	                  ->RemoveDynamic(Head.Get(), &UItemWidget::SetItem);

	InventoryComponent->GetBackpack()->GetOnInventoryUpdated()
	                  ->RemoveDynamic(Backpack.Get(), &UItemWidget::SetItem);

	InventoryComponent->GetRightHand()->GetOnInventoryUpdated()
	                  ->RemoveDynamic(RightHand.Get(), &UItemWidget::SetItem);

	InventoryComponent->GetLeftHand()->GetOnInventoryUpdated()
	                  ->RemoveDynamic(LeftHand.Get(), &UItemWidget::SetItem);

	InventoryComponent->GetArmorPlace()->GetOnInventoryUpdated()
	                  ->RemoveDynamic(Chest.Get(), &UItemWidget::SetItem);

	InventoryComponent->GetLegs()->GetOnInventoryUpdated()
	                  ->RemoveDynamic(Legs.Get(), &UItemWidget::SetItem);

	InventoryComponent->GetBoots()->GetOnInventoryUpdated()
	                  ->RemoveDynamic(Boots.Get(), &UItemWidget::SetItem);
}

void UEquipmentUserWidget::Subscribe(UInventoryComponent* InventoryComponent)
{
	InventoryComponent->GetHelmetPlace()->GetOnInventoryUpdated()
	                  ->AddDynamic(Head.Get(), &UItemWidget::SetItem);

	InventoryComponent->GetBackpack()->GetOnInventoryUpdated()
	                  ->AddDynamic(Backpack.Get(), &UItemWidget::SetItem);

	InventoryComponent->GetRightHand()->GetOnInventoryUpdated()
	                  ->AddDynamic(RightHand.Get(), &UItemWidget::SetItem);

	InventoryComponent->GetLeftHand()->GetOnInventoryUpdated()
	                  ->AddDynamic(LeftHand.Get(), &UItemWidget::SetItem);

	InventoryComponent->GetArmorPlace()->GetOnInventoryUpdated()
	                  ->AddDynamic(Chest.Get(), &UItemWidget::SetItem);

	InventoryComponent->GetLegs()->GetOnInventoryUpdated()
	                  ->AddDynamic(Legs.Get(), &UItemWidget::SetItem);

	InventoryComponent->GetBoots()->GetOnInventoryUpdated()
	                  ->AddDynamic(Boots.Get(), &UItemWidget::SetItem);
}


void UEquipmentUserWidget::Setup(UInventoryComponent* InventoryComponent)
{
	if (CurrentInventoryComponent)
	{
		Unsubscribe(CurrentInventoryComponent);
	}

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
