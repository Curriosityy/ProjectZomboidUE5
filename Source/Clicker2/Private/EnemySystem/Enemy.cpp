// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySystem\Enemy.h"

#include "Player\HPComponent.h"

UMeshComponent* AEnemy::GetAimableMesh()
{
	return GetMesh();
}

IDamageable* AEnemy::GetDamageable()
{
	return this;
}

bool AEnemy::CanBeAimed()
{
	return true;
}

void AEnemy::DealDamage(int damage, UObject* DamageDealer, bool Critical)
{
	HPComponent->DealDamage(damage);
}

int AEnemy::GetHP()
{
	return HPComponent->GetCurrentHp();
}

// Sets default values
AEnemy::AEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HPComponent = CreateDefaultSubobject<UHPComponent>("HPComponent");
	HPComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
