#include "ItemSystem\ItemHelper.h"

#include "ItemSystem\BasicItemContainer.h"
#include "ItemSystem\EquippedItem.h"
#include "ItemSystem\InventoryComponent.h"
#include "ItemSystem\Item.h"
#include "ItemSystem\ItemHolder.h"

bool ItemHelper::AddItemToNewHolder(IItemHolder* NewHolder, UItem* Item)
{
	IItemHolder* oldHolder = Item->GetHolder();

	if (oldHolder && NewHolder->CanAddItem(Item) && oldHolder->RemoveItem(Item))
	{
		if (NewHolder->AddItem(Item))
		{
			Item->SetNewOwner(NewHolder);

			return true;
		}

		oldHolder->AddItem(Item);
	}

	return false;
}

bool ItemHelper::IsInventoryItemHolder(AClicker2Character* Owner, IItemHolder* GetHolder)
{
	auto invComponent = Owner->GetInventoryComponent();
	bool isInventory = false;

	isInventory |= (invComponent->GetHeldItems() == GetHolder);
	isInventory |= (invComponent->GetHelmetPlace() == GetHolder);
	isInventory |= (invComponent->GetBackpack() == GetHolder);
	isInventory |= (invComponent->GetRightHand() == GetHolder);
	isInventory |= (invComponent->GetArmorPlace() == GetHolder);
	isInventory |= (invComponent->GetLeftHand() == GetHolder);
	isInventory |= (invComponent->GetLegs() == GetHolder);
	isInventory |= (invComponent->GetBoots() == GetHolder);

	return isInventory;
}
