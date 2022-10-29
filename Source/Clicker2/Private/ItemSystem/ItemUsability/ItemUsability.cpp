// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSystem\ItemUsability\ItemUsability.h"

#include "ItemSystem\ItemHolder.h"

void UItemUsability::UseItem(AClicker2Character* user, UItem* Item)
{
	if (useBPFirst)
	{
		BPUse(user, Item);
		Use(user, Item);
	}
	else
	{
		Use(user, Item);
		BPUse(user, Item);
	}
}
