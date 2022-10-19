// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Pickupable.generated.h"

// This class does not need to be modified.
class UItem;
UINTERFACE()
class UPickupable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CLICKER2_API IPickupable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool CanPickUp() PURE_VIRTUAL(CanPickUp, return false;);
	virtual UItem* GetItemInfo() PURE_VIRTUAL(GetItemInfo, return nullptr;);
	virtual UItem* PickUp() PURE_VIRTUAL(PickUp, return nullptr;);
};
