// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSystem/WeaponItemData.h"

TSubclassOf<UWeaponAttackComponent> UWeaponItemData::GetWeaponAttackComponent() const
{
	return WeaponAttackComponent;
}

UWeaponItemData::UWeaponItemData()
{
	Range=1;
	TwoHanded=true;
}

float UWeaponItemData::GetRange() const
{
	return Range;
}

bool UWeaponItemData::IsTwoHanded() const
{
	return TwoHanded;
}
