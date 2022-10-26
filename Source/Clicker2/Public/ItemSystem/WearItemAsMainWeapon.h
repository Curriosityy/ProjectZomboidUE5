// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WearItemAsMain.h"
#include "ItemSystem\ItemUsability.h"
#include "WearItemAsMainWeapon.generated.h"

/**
 * 
 */
UCLASS()
class CLICKER2_API UWearItemAsMainWeapon : public UWearItemAsMain
{
	GENERATED_BODY()

public:
	virtual UEquippedItem* GetMainHolder(AClicker2Character* User) override;
};
