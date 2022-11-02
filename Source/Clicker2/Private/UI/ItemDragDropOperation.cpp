// Fill out your copyright notice in the Description page of Project Settings.


#include "UI\ItemDragDropOperation.h"
#include "ItemSystem\Item.h"

UItem* UItemDragDropOperation::GetItemPayload()
{
	return Cast<UItem>(Payload);
}
