// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemSystem\ItemUsability\WearItemAsMain.h"
#include "MyWearItemAsMainLegs.generated.h"

/**
 * 
 */
UCLASS()
class CLICKER2_API UMyWearItemAsMainLegs : public UWearItemAsMain
{
	GENERATED_BODY()

public:
	virtual UEquippedItem* GetItemDestination(AClicker2Character* User) override;
};
