// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemSystem/ItemDatas/ItemData.h"
#include "WeaponItemData.generated.h"

/**
 * 
 */
UCLASS()
class CLICKER2_API UWeaponItemData : public UItemData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	float Range;
	
	UPROPERTY(EditDefaultsOnly)
	bool TwoHanded;

public:
	UWeaponItemData();
	float GetRange() const;
	bool IsTwoHanded() const;
};
