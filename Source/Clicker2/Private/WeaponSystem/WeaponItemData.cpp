// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSystem\WeaponItemData.h"

float UWeaponItemData::GetDamage() const
{
	return Damage;
}

float UWeaponItemData::GetCriticalMultiplier() const
{
	return CriticalMultiplier;
}

WeaponAttackType UWeaponItemData::GetAttackType() const
{
	return AttackType;
}

TSubclassOf<UWeaponAttackComponent> UWeaponItemData::GetWeaponAttackComponent() const
{
	return WeaponAttackComponent;
}

UWeaponItemData::UWeaponItemData()
{
	Range = 1;
	Damage = 10;
	CriticalMultiplier = 10;
	TwoHanded = true;
}

float UWeaponItemData::GetRange() const
{
	return Range;
}

bool UWeaponItemData::IsTwoHanded() const
{
	return TwoHanded;
}
