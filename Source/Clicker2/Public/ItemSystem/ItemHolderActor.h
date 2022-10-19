// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemHolder.h"
#include "ItemSystem/ItemActor.h"
#include "ItemHolderActor.generated.h"

/**
 * 
 */
UCLASS()
class CLICKER2_API AItemHolderActor : public AItemActor, public IItemHolder
{
	GENERATED_BODY()
	
	TArray<UItem*> HeldItems;
	FOnInventoryUpdated OnInventoryUpdated;
public:
	
	virtual int GetSize() override;
	virtual EItemType GetHeldItemType() override;
	virtual TArray<UItem*> GetItems() override;
	virtual bool CanAddItem(UItem* item) override;
	virtual bool AddItem(IItemHolder* previousOwner, UItem* item) override;
	virtual bool RemoveItem(UItem* item) override;
	virtual float GetWeightOfHeldItems() override;
	virtual FOnInventoryUpdated* GetOnInventoryUpdated() override;
	virtual bool CanPickUp() override;

};
