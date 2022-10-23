// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponSystem\WeaponAttackComponent.h"
#include "RaycastShooting.generated.h"

class AClicker2Character;
/**
 * 
 */
UCLASS()
class CLICKER2_API URaycastShooting : public UWeaponAttackComponent
{
	GENERATED_BODY()

	UPROPERTY()
	;
	bool bIsAiming;

protected:
	virtual void BeginPlay() override;

	void Aim(float TickDelta);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(Transient, NonTransactional)
	TObjectPtr<AClicker2Character> CurrentAimed;

	void SetCurrentAimed(AClicker2Character* NewAimed);

	UPROPERTY(meta=(ClampMax = "1", ClampMin="0"))
	float HitPossibility;

public:
	URaycastShooting();

	virtual void StartAim() override;

	virtual void StopAim() override;

	virtual void Attack() override;
};
