// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemSystem/ItemDatas/ItemData.h"
#include "BackpackItemData.generated.h"

/**
 * 
 */
UCLASS(Blueprintable,NotPlaceable)
class CLICKER2_API UBackpackItemData : public UItemData
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category="Item")
	int SlotCount;

	UPROPERTY(EditAnywhere, Category="Item")
	float WeightMultipliedBy;
public:
	UBackpackItemData();

	int GetSlots();

	float GetWeightMultipliedBy();
};
