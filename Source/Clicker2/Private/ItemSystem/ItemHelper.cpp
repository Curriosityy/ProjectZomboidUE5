#include "ItemSystem\ItemHelper.h"
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
