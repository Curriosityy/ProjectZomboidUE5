#include "ItemSystem\ItemHelper.h"
#include "ItemSystem\Item.h"
#include "ItemSystem\ItemHolder.h"

bool ItemHelper::AddItemToNewHolder(IItemHolder* OldHolder, IItemHolder* NewHolder, UItem* Item)
{
	if (OldHolder->RemoveItem(Item))
	{
		if (NewHolder->AddItem(Item))
		{
			Item->SetNewOwner(NewHolder);
		}
	}

	return false;
}
