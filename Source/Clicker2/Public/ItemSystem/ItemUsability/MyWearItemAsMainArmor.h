// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemSystem\ItemUsability\WearItemAsMain.h"
#include "MyWearItemAsMainArmor.generated.h"

/**
 * 
 */
UCLASS()
class CLICKER2_API UMyWearItemAsMainArmor : public UWearItemAsMain
{
	GENERATED_BODY()

public:
	virtual UEquippedItem* GetMainHolder(AClicker2Character* User) override;
};
