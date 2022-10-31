// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemSystem\ItemUsability\WearItemAsMain.h"
#include "MyWearItemAsMainOffhand.generated.h"

/**
 * 
 */
UCLASS()
class CLICKER2_API UMyWearItemAsMainOffhand : public UWearItemAsMain
{
	GENERATED_BODY()

public:
	virtual UEquippedItem* GetItemDestination(AClicker2Character* User) override;
};
