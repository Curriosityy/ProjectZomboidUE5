#include "AttackSystem\DealDamageHelper.h"

#include "macros.h"
#include "AttackSystem\IDamageable.h"
#include "WeaponSystem\WeaponItemData.h"

void DealDamageHelper::BaseDealDamage(IDamageable* Target, UObject* attacker, UWeaponItemData* Weapon,
                                      float HitPossibility)
{
	float randomHit = FMath::RandRange(0.f, 1.0f);

	if (randomHit <= HitPossibility)
	{
		bool isCritical = FMath::RandRange(HitPossibility, 1.0f) >= 0.9f;

		PRINT_DEBUG("%f", HitPossibility);


		float damage = Weapon->GetDamage() * (isCritical
			                                      ? Weapon->GetCriticalMultiplier()
			                                      : 1);
		Target->DealDamage(damage,
		                   attacker,
		                   isCritical);
	}
}
