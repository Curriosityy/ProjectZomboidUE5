// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSystem/Item.h"
#include "ItemSystem/ItemDatas/ItemData.h"
#include "ItemSystem/ItemUsability.h"

void UItem::Setup(UItemData* itemData)
{
	ItemData = itemData;
}

void UItem::Use(AClicker2Character* user) const
{
	for (auto Element : ItemData->GetItemUsabilities())
	{
		Cast<UItemUsability>(Element->GetDefaultObject())->UseItem(user);
	}
}

UItemData* UItem::GetItemData()
{
	return ItemData;
}

template<class T>
T* UItem::GetItemData()
{
	return dynamic_cast<T*>(ItemData);
}
