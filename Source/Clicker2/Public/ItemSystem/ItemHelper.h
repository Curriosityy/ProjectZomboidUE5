#pragma once
#include "Player\Clicker2Character.h"
#include "UI\QuickEquipUserWidget.h"

class IItemHolder;
class UItem;

class ItemHelper
{
public:
	bool static AddItemToNewHolder(IItemHolder* NewHolder, UItem* Item);

	bool static IsInventoryItemHolder(AClicker2Character* Owner, IItemHolder* GetHolder);
};
