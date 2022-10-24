// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSystem\RaycastShooting.h"

#include "macros.h"
#include "AttackSystem\Aimable.h"
#include "AttackSystem\IDamageable.h"
#include "GameMode\Clicker2GameMode.h"
#include "ItemSystem\EquippedItem.h"
#include "ItemSystem\InventoryComponent.h"
#include "ItemSystem\Item.h"
#include "Player\Clicker2Character.h"
#include "WeaponSystem\WeaponItemData.h"

URaycastShooting::URaycastShooting()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void URaycastShooting::BeginPlay()
{
	Super::BeginPlay();
}

void URaycastShooting::Aim(float TickDelta)
{
	FVector position = Owner->GetTransform().GetLocation();
	FVector forward = Owner->GetActorForwardVector();
	float distance = 1000;
	int numberOfRay = 1;
	float attackAngle = 0;
	FHitResult Hit;
	FCollisionQueryParams params = FCollisionQueryParams::DefaultQueryParam;
	params.AddIgnoredActor(Owner);

	GetWorld()->LineTraceSingleByChannel(Hit, position, position + (forward * distance), ECC_GameTraceChannel1,
	                                     params);

	if (IAimable* target = dynamic_cast<IAimable*>(Hit.GetActor()))
	{
		if (target == CurrentAimed.GetInterface())
		{
			HitPossibility += TickDelta;

			if (HitPossibility >= 1)
			{
				HitPossibility = 1;
			}

			GetWorld()->GetAuthGameMode<AClicker2GameMode>()->SetAimPostProcessingOverlayValue(HitPossibility);
		}
		else
		{
			SetCurrentTarget(target);
			HitPossibility = 0;
		}
	}
	else
	{
		HitPossibility = 0;
		SetCurrentTarget(nullptr);
	}

	DrawDebugLine(GetWorld(), position, position + (forward * distance), FColor::Red);
}

void URaycastShooting::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsAiming)
	{
		Aim(DeltaTime);
	}
}

void URaycastShooting::SetCurrentTarget(IAimable* NewAimed)
{
	if (CurrentAimed)
	{
		CurrentAimed->GetAimableMesh()->SetRenderCustomDepth(false);
	}


	CurrentAimed = NewAimed ? NewAimed->_getUObject() : nullptr;

	if (CurrentAimed)
	{
		CurrentAimed->GetAimableMesh()->SetRenderCustomDepth(true);
	}
}


void URaycastShooting::StartAim()
{
	HitPossibility = 0;
	bIsAiming = true;
}

void URaycastShooting::StopAim()
{
	HitPossibility = 0;
	bIsAiming = false;
	SetCurrentTarget(nullptr);
}

void URaycastShooting::Attack()
{
	if (!bIsAiming)
	{
		return;
	}

	float randomHit = FMath::RandRange(0.f, 1.0f);

	if (randomHit <= HitPossibility)
	{
		bool isCritical = FMath::RandRange(HitPossibility, 1.0f) >= 0.9f;

		UWeaponItemData* weaponData = Cast<UWeaponItemData>(
			Owner->GetInventoryComponent()->GetRightHand()->GetItem()->GetItemData());

		float damage = weaponData->GetDamage() * (isCritical
			                                          ? weaponData->GetCriticalMultiplier()
			                                          : 1);
		CurrentAimed->GetDamageable()->DealDamage(damage,
		                                          Owner,
		                                          isCritical);
	}

	PRINT_DEBUG("URaycastShooting::Attack");
}
