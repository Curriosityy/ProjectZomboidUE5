// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSystem/ItemUsability.h"

void UItemUsability::UseItem(AClicker2Character* user)
{
	if (useBPFirst)
	{
		BPUse(user);
		Use(user);
	}
	else
	{
		Use(user);
		BPUse(user);
	}
}
