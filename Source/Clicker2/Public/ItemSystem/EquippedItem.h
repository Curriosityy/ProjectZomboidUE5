// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemHolder.h"
#include "EquippedItem.generated.h"

/**
 * 
 */
UCLASS(DefaultToInstanced, Blueprintable)
class CLICKER2_API UEquippedItem : public UObject, public IItemHolder
{
	GENERATED_BODY()

private:
	EItemType HeldItemType;
	
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UItem> Item;

	FOnInventoryUpdated OnEquippedItemUpdated;
public:
	void Initialize(EItemType itemType);
	virtual int GetSize() override;
	virtual EItemType GetHeldItemType() override;
	virtual TArray<UItem*> GetItems() override;
	virtual UItem* GetItem();
	virtual bool CanAddItem(UItem* item) override;
	virtual bool AddItem(IItemHolder* previousOwner, UItem* item) override;
	virtual bool RemoveItem(UItem* item) override;
	virtual float GetWeightOfHeldItems() override;
	virtual FOnInventoryUpdated* GetOnInventoryUpdated() override;
};
