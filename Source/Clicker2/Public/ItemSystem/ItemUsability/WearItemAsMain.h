// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemSystem\ItemUsability\ItemUsability.h"
#include "WearItemAsMain.generated.h"
class UEquippedItem;

/**
 * 
 */
UCLASS(Abstract)
class CLICKER2_API UWearItemAsMain : public UItemUsability
{
	GENERATED_BODY()

public:
	virtual void Use(AClicker2Character* User, IItemHolder* CurrentItemHolder, UItem* Item) override;

	virtual UEquippedItem* GetMainHolder(AClicker2Character* User) PURE_VIRTUAL(GetMainHolder, return nullptr;);
};
