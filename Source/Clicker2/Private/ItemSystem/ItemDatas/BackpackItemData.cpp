// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSystem\ItemDatas\BackpackItemData.h"

UBackpackItemData::UBackpackItemData()
{
	ItemType = EItemType::Backpack;
}

int UBackpackItemData::GetSlots()
{
	return SlotCount;
}

float UBackpackItemData::GetWeightMultipliedBy()
{
	return WeightMultipliedBy;
}
