// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemHolder.h"
#include "Item.generated.h"

class UItemData;
class AClicker2Character;
enum class EItemType : uint8;
/**
 * 
 */
UCLASS(DefaultToInstanced, NotPlaceable, NotBlueprintable, Transient)
class CLICKER2_API UItem : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
	float Durability;

	UPROPERTY(Transient, NonTransactional)
	TObjectPtr<UItemData> ItemData;

public:
	void Setup(UItemData* itemData);

	void Use(AClicker2Character* user, IItemHolder* ItemHolder);

	UItemData* GetItemData();

	template <class T>
	T* GetItemData();
};
