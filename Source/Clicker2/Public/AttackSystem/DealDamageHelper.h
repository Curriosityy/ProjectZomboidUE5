#pragma once
class IDamageable;
class UObject;
class UWeaponItemData;


class DealDamageHelper
{
public:
	static void BaseDealDamage(IDamageable* Target, UObject* attacker, UWeaponItemData* Weapon,
	                           float HitPossibility);
};
