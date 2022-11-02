// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackSystem\Aimable.h"
#include "AttackSystem\IDamageable.h"
#include "GameFramework\Character.h"
#include "Player\HPComponent.h"
#include "Enemy.generated.h"

UCLASS()
class CLICKER2_API AEnemy : public ACharacter, public IAimable, public IDamageable
{
	GENERATED_BODY()

	TObjectPtr<UHPComponent> HPComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual UMeshComponent* GetAimableMesh() override;

	virtual IDamageable* GetDamageable() override;

	virtual bool CanBeAimed() override;

	virtual void DealDamage(int damage, UObject* DamageDealer, bool Critical) override;

	virtual int GetHP() override;

	AEnemy();
};
