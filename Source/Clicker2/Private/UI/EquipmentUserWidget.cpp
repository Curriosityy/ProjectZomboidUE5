// Fill out your copyright notice in the Description page of Project Settings.


#include "UI\EquipmentUserWidget.h"

#include "ItemSystem\EquippedItem.h"
#include "ItemSystem\InventoryComponent.h"
#include "ItemSystem\Item.h"
#include "ItemSystem\ItemHelper.h"
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

void UEquipmentUserWidget::OnItemDrop(UItemWidget* Reciver, UItemDragDropOperation* Payload)
{
	if (Payload->bIsDragFromQuickWidget)
	{
		return;
	}

	UItem* item = Payload->GetItemPayload();
	IItemHolder* reciverHolder = GetItemHolderBasedOnItemWidget(Reciver);

	if (UWeaponItemData* weapon = Cast<UWeaponItemData>(item->GetItemData()))
	{
		if (reciverHolder == CurrentInventoryComponent->GetLeftHand() ||
			reciverHolder == CurrentInventoryComponent->GetRightHand())
		{
			reciverHolder = CurrentInventoryComponent->GetRightHand();
		}
	}


	ItemHelper::AddItemToNewHolder(reciverHolder, item);
}

void UEquipmentUserWidget::Unsubscribe(UEquippedItem* itemHolder, UItemWidget* widget)
{
	itemHolder->GetOnInventoryUpdated()
	          ->RemoveDynamic(widget, &UItemWidget::SetupByItemholder);
	widget->OnItemDrop.RemoveDynamic(this, &UEquipmentUserWidget::OnItemDrop);
}

void UEquipmentUserWidget::Subscribe(UEquippedItem* itemHolder, UItemWidget* itemWidhet)
{
	itemHolder->GetOnInventoryUpdated()
	          ->AddDynamic(itemWidhet, &UItemWidget::SetupByItemholder);

	itemWidhet->OnItemDrop.AddDynamic(this, &UEquipmentUserWidget::OnItemDrop);
}

void UEquipmentUserWidget::Subscribe(UInventoryComponent* InventoryComponent)
{
	Subscribe(InventoryComponent->GetHelmetPlace(), Head);
	Subscribe(InventoryComponent->GetBackpack(), Backpack);
	Subscribe(InventoryComponent->GetRightHand(), RightHand);
	Subscribe(InventoryComponent->GetLeftHand(), LeftHand);
	Subscribe(InventoryComponent->GetArmorPlace(), Chest);
	Subscribe(InventoryComponent->GetLegs(), Legs);
	Subscribe(InventoryComponent->GetBoots(), Boots);

	InventoryComponent->GetRightHand()->GetOnInventoryUpdated()
	                  ->AddDynamic(this, &UEquipmentUserWidget::DoubleHandWearTest);
}

void UEquipmentUserWidget::Unsubscribe(UInventoryComponent* InventoryComponent)
{
	Unsubscribe(InventoryComponent->GetHelmetPlace(), Head);
	Unsubscribe(InventoryComponent->GetBackpack(), Backpack);
	Unsubscribe(InventoryComponent->GetRightHand(), RightHand);
	Unsubscribe(InventoryComponent->GetLeftHand(), LeftHand);
	Unsubscribe(InventoryComponent->GetArmorPlace(), Chest);
	Unsubscribe(InventoryComponent->GetLegs(), Legs);
	Unsubscribe(InventoryComponent->GetBoots(), Boots);

	InventoryComponent->GetRightHand()->GetOnInventoryUpdated()
	                  ->RemoveDynamic(this, &UEquipmentUserWidget::DoubleHandWearTest);
}

void UEquipmentUserWidget::Setup(UInventoryComponent* InventoryComponent)
{
	if (CurrentInventoryComponent)
	{
		Unsubscribe(CurrentInventoryComponent);
	}

	CurrentInventoryComponent = InventoryComponent;
	Subscribe(CurrentInventoryComponent);

	Head->SetupByItemholder(InventoryComponent->GetHelmetPlace());
	Backpack->SetupByItemholder(InventoryComponent->GetBackpack());
	RightHand->SetupByItemholder(InventoryComponent->GetRightHand());
	LeftHand->SetupByItemholder(InventoryComponent->GetLeftHand());
	Chest->SetupByItemholder(InventoryComponent->GetArmorPlace());
	Legs->SetupByItemholder(InventoryComponent->GetLegs());
	Boots->SetupByItemholder(InventoryComponent->GetBoots());

	DoubleHandWearTest(InventoryComponent->GetRightHand());
}


void UEquipmentUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Head->SetItemIndex(0);
	Backpack->SetItemIndex(0);
	RightHand->SetItemIndex(0);
	LeftHand->SetItemIndex(0);
	Chest->SetItemIndex(0);
	Legs->SetItemIndex(0);
	Boots->SetItemIndex(0);
}

IItemHolder* UEquipmentUserWidget::GetItemHolderBasedOnItemWidget(UItemWidget* Reciver)
{
	IItemHolder* itemHolder = nullptr;

	if (Reciver == Head)
	{
		itemHolder = CurrentInventoryComponent->GetHelmetPlace();
	}
	else if (Reciver == Backpack)
	{
		itemHolder = CurrentInventoryComponent->GetBackpack();
	}
	else if (Reciver == RightHand)
	{
		itemHolder = CurrentInventoryComponent->GetRightHand();
	}
	else if (Reciver == Chest)
	{
		itemHolder = CurrentInventoryComponent->GetArmorPlace();
	}
	else if (Reciver == LeftHand)
	{
		itemHolder = CurrentInventoryComponent->GetLeftHand();
	}
	else if (Reciver == Legs)
	{
		itemHolder = CurrentInventoryComponent->GetLegs();
	}
	else if (Reciver == Boots)
	{
		itemHolder = CurrentInventoryComponent->GetBoots();
	}

	return itemHolder;
}
