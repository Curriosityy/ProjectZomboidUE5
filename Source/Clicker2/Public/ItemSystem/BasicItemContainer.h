// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "ItemHolder.h"
#include "BasicItemContainer.generated.h"

class AClicker2Character;
/**
 * Basic item container that can hold multiple items.
 */
UCLASS(DefaultToInstanced,NotBlueprintable,NotPlaceable)
class CLICKER2_API UBasicItemContainer : public UObject, public IItemHolder
{

	GENERATED_BODY()
private:
	UPROPERTY()
	TObjectPtr<AClicker2Character> Owner;

	UPROPERTY(VisibleAnywhere,DisplayName="Held Items")
	TArray<TObjectPtr<UItem>> ItemsHeld;
	
	FOnInventoryUpdated OnInventoryUpdated;
public:
	UBasicItemContainer();
	void Initialize(AClicker2Character* Owner);
	
	virtual int GetSize() override;
	virtual EItemType GetHeldItemType() override;
	virtual TArray<UItem*> GetItems() override;
	virtual bool CanAddItem(UItem* item) override;
	virtual bool AddItem(IItemHolder* previousOwner, UItem* item) override;
	virtual bool RemoveItem(UItem* item) override;
	virtual float GetWeightOfHeldItems() override;
	virtual FOnInventoryUpdated* GetOnInventoryUpdated() override;
	
};
