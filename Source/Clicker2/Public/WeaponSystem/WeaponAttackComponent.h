// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponAttackComponent.generated.h"

class AClicker2Character;

UCLASS(Abstract, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CLICKER2_API UWeaponAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponAttackComponent();

protected:
	UPROPERTY(Transient,NonTransactional)
	TObjectPtr<AClicker2Character> Owner;
	
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	virtual void StartAim() PURE_VIRTUAL(StartAim);
	virtual void StopAim() PURE_VIRTUAL(StopAim);
	virtual void Attack() PURE_VIRTUAL(Attack);
};
