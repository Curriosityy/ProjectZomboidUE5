// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSystem\Item.h"
#include "ItemSystem\ItemDatas\ItemData.h"
#include "ItemSystem\ItemUsability\ItemUsability.h"

IItemHolder* UItem::GetHolder() const
{
	return Holder.GetInterface();
}

void UItem::Setup(UItemData* itemData)
{
	ItemData = itemData;
}

void UItem::Use(AClicker2Character* User, IItemHolder* ItemHolder)
{
	for (TSubclassOf<UItemUsability> Element : ItemData->GetItemUsabilities())
	{
		Cast<UItemUsability>(Element->GetDefaultObject())->UseItem(User, this);
	}
}

UItemData* UItem::GetItemData()
{
	return ItemData;
}

void UItem::SetNewOwner(IItemHolder* NewOwner)
{
	Holder = NewOwner->_getUObject();
}

template <class T>
T* UItem::GetItemData()
{
	return dynamic_cast<T*>(ItemData);
}
