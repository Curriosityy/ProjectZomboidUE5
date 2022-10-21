// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponSystem/WeaponAttackComponent.h"
#include "RaycastShooting.generated.h"

class AClicker2Character;
/**
 * 
 */
UCLASS()
class CLICKER2_API URaycastShooting : public UWeaponAttackComponent
{
	GENERATED_BODY()

	UPROPERTY();
	bool bIsAiming;
	
protected:
	virtual void BeginPlay() override;
	void Aim();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	URaycastShooting();
	virtual void StartAim() override;
	virtual void StopAim() override;
	virtual void Attack() override;
	

};
