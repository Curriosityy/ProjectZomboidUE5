// Fill out your copyright notice in the Description page of Project Settings.


#include "UI\EquipmentUserWidget.h"

#include "ItemSystem\EquippedItem.h"
#include "ItemSystem\InventoryComponent.h"
#include "ItemSystem\Item.h"
#include "UI\ItemWidget.h"
#include "WeaponSystem\WeaponItemData.h"

void UEquipmentUserWidget::DoubleHandWearTest(TScriptInterface<IItemHolder> ItemHolder)
{
	ESlateVisibility visibility = ESlateVisibility::Visible;
	auto heldItem = ItemHolder->GetItems()[0];

	if (heldItem)
	{
		if (auto itemData = Cast<UWeaponItemData>(heldItem->GetItemData()))
		{
			if (itemData->IsTwoHanded())
			{
				visibility = ESlateVisibility::Hidden;
			}
		}
	}

	LeftHand->SetVisibility(visibility);
}

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

	InventoryComponent->GetRightHand()->GetOnInventoryUpdated()
	                  ->RemoveDynamic(this, &UEquipmentUserWidget::DoubleHandWearTest);
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

	InventoryComponent->GetRightHand()->GetOnInventoryUpdated()
	                  ->AddDynamic(this, &UEquipmentUserWidget::DoubleHandWearTest);


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

	DoubleHandWearTest(InventoryComponent->GetRightHand());

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
