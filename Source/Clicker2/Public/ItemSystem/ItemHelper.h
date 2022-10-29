#pragma once

class IItemHolder;
class UItem;

class ItemHelper
{
public:
	bool static AddItemToNewHolder(IItemHolder* OldHolder, IItemHolder* NewHolder, UItem* Item);
};
