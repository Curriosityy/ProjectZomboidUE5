// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemUsability.generated.h"
class UItem;
class AClicker2Character;
class IItemHolder;

/**
 * 
 */
UCLASS(Abstract, Blueprintable, NotPlaceable)
class CLICKER2_API UItemUsability : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	bool useBPFirst = false;

protected:
	//Method to implement when, want to write c++ usability of item
	virtual void Use(AClicker2Character* user, IItemHolder* ItemHolder, UItem* Item) PURE_VIRTUAL(UItemUsability,);

	//Method to implement 
	//UFUNCTION(BlueprintImplementableEvent)
	//void BPUse(AClicker2Character* user, IItemHolder* ItemHolder, UItem* Item);

public:
	virtual void UseItem(AClicker2Character* user, IItemHolder* ItemHolder, UItem* Item);
};
