// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSystem\RaycastShooting.h"

#include "macros.h"
#include "Engine\PostProcessVolume.h"
#include "GameMode\Clicker2GameMode.h"
#include "Player\Clicker2Character.h"

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

	if (AClicker2Character* target = dynamic_cast<AClicker2Character*>(Hit.GetActor()))
	{
		if (target == CurrentAimed)
		{
			HitPossibility += TickDelta;
			GetWorld()->GetAuthGameMode<AClicker2GameMode>()->SetAimPostProcessingOverlayValue(HitPossibility);
		}
		else
		{
			CurrentAimed->GetMesh()->SetRenderCustomDepth(false);

			CurrentAimed = target;
			CurrentAimed->GetMesh()->SetRenderCustomDepth(true);
			HitPossibility = 0;
		}
	}
	else
	{
		if (CurrentAimed)
		{
			CurrentAimed->GetMesh()->SetRenderCustomDepth(false);
		}
		HitPossibility = 0;
		CurrentAimed = nullptr;
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


void URaycastShooting::StartAim()
{
	PRINT_DEBUG("URaycastShooting::StartAim");
	HitPossibility = 0;
	bIsAiming = true;
}

void URaycastShooting::StopAim()
{
	PRINT_DEBUG("URaycastShooting::StopAim");
	HitPossibility = 0;
	bIsAiming = false;
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
		//ShootRaycast
	}

	PRINT_DEBUG("URaycastShooting::Attack");
}
