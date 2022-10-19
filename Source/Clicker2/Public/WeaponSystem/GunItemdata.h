// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponItemData.h"
#include "GunItemdata.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CLICKER2_API UGunItemdata : public UWeaponItemData
{
	GENERATED_BODY()


	UPROPERTY(EditDefaultsOnly)
	float BaseAim;

public:
	UGunItemdata();
};
