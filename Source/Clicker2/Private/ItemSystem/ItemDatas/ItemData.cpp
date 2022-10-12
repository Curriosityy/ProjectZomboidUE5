// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSystem/ItemDatas/ItemData.h"


FGuid UItemData::GetID() const
{
	return ID;
}

FText UItemData::GetItemName() const
{
	return ItemName;
}

FText UItemData::GetItemDescription() const
{
	return ItemDescription;
}

bool UItemData::IsStackable() const
{
	return Stackable;
}

TObjectPtr<UTexture2D> UItemData::GetItemThumbnail() const
{
	return ItemThumbnail;
}

TObjectPtr<UStaticMesh> UItemData::GetItemInWorld() const
{
	return ItemInWorld;
}

TArray<TSubclassOf<UItemUsability>> UItemData::GetItemUsabilities()
{
	return ItemUsabilities;
}

EItemType UItemData::GetItemType() const
{
	return ItemType;
}

float UItemData::GetWeight()
{
	return Weight;
}



