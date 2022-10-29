// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemDatas\ItemData.h"
#include "UObject\Interface.h"
#include "ItemHolder.generated.h"

class UItem;
enum class EItemType : uint8;

// This class does not need to be modified.
UINTERFACE()
class CLICKER2_API UItemHolder : public UInterface
{
	GENERATED_BODY()
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryUpdated, TScriptInterface<IItemHolder>, itemHolderUpdated);

/**
 * 
 */
class CLICKER2_API IItemHolder
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.

public:
	virtual int GetSize() PURE_VIRTUAL(GetSize, return 0;);

	virtual EItemType GetHeldItemType() PURE_VIRTUAL(GetHeldItemType, return static_cast<EItemType>(0););

	virtual TArray<UItem*> GetItems() PURE_VIRTUAL(GetItems, return TArray<UItem*>(););

	bool CanHeldItemType(EItemType itemType) { return (itemType & GetHeldItemType()) != EItemType::None; }

	virtual bool CanAddItem(UItem* item) PURE_VIRTUAL(CanAddItem, return false;);

	virtual bool AddItem(UItem* item) PURE_VIRTUAL(AddItem, return false;);

	virtual bool RemoveItem(UItem* item) PURE_VIRTUAL(RemoveItem, return false;);

	virtual float GetWeightOfHeldItems() PURE_VIRTUAL(IItemHolder, return 0.f;);

	virtual FOnInventoryUpdated* GetOnInventoryUpdated() PURE_VIRTUAL(RemoveItem, return nullptr;);
};
