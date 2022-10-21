// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSystem/RaycastShooting.h"

#include "macros.h"
#include "Player/Clicker2Character.h"

URaycastShooting::URaycastShooting()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void URaycastShooting::BeginPlay()
{
	Super::BeginPlay();
}

void URaycastShooting::Aim()
{
	TArray<FHitResult> Hits;

	FVector position = Owner->GetTransform().GetLocation();
	FVector forward = Owner->GetActorForwardVector();
	float distance = 1000;
	int numberOfRay = 1;
	float attackAngle = 0;
	FHitResult Hit;
	FCollisionQueryParams params = FCollisionQueryParams::DefaultQueryParam;
	params.AddIgnoredActor(Owner);
	for(int i=0;i<numberOfRay;i++)
	{
		GetWorld()->LineTraceSingleByChannel(Hit,position, position+(forward*distance), ECC_GameTraceChannel1, params);
		Hits.Add(Hit);

		if(AClicker2Character* target = dynamic_cast<AClicker2Character*>(Hit.GetActor()))
		{
			PRINT_DEBUG("TARGET %s",*target->GetName());
		}

		DrawDebugLine(GetWorld(),position,position+(forward*distance),FColor::Red);
	}
}

void URaycastShooting::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(bIsAiming)
	{
		Aim();
	}
}



void URaycastShooting::StartAim()
{
	PRINT_DEBUG("URaycastShooting::StartAim");
	bIsAiming=true;
}

void URaycastShooting::StopAim()
{
	PRINT_DEBUG("URaycastShooting::StopAim");
	bIsAiming=false;
}

void URaycastShooting::Attack()
{
	if(!bIsAiming)
		return;

	PRINT_DEBUG("URaycastShooting::Attack");
}
