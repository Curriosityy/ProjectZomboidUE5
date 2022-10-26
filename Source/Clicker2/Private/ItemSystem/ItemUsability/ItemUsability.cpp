// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSystem\ItemUsability\ItemUsability.h"

#include "ItemSystem\ItemHolder.h"

void UItemUsability::UseItem(AClicker2Character* user, IItemHolder* ItemHolder, UItem* Item)
{
	if (useBPFirst)
	{
		//BPUse(user, ItemHolder, Item);
		Use(user, ItemHolder, Item);
	}
	else
	{
		Use(user, ItemHolder, Item);
		//BPUse(user, ItemHolder, Item);
	}
}
