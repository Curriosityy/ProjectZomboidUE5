// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AttackSystem\Aimable.h"
#include "AttackSystem\IDamageable.h"
#include "GameFramework\Character.h"
#include "Clicker2Character.generated.h"

class ULineOfSightComponent;
class UGunItemdata;
class USearchForPickupColliderComponent;
class UPlayerStatsComponent;
class UItem;
class USpringArmComponent;
class UCameraComponent;
class UHPComponent;
class UInventoryComponent;
class IDamageable;

UCLASS(Blueprintable)
class AClicker2Character : public ACharacter, public IAimable, public IDamageable
{
	GENERATED_BODY()

public:
	AClicker2Character(const FObjectInitializer& ObjectInitializer);

	virtual void DealDamage(int damage, UObject* DamageDealer, bool Critical) override;

	virtual int GetHP() override;

	virtual UMeshComponent* GetAimableMesh() override;

	virtual IDamageable* GetDamageable() override;

	virtual void Tick(float DeltaSeconds) override;

	FORCEINLINE UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }

	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	USearchForPickupColliderComponent* GetSearchItemComponent() const;

	UInventoryComponent* GetInventoryComponent() const;

	UPlayerStatsComponent* GetStatsComponent() const;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = "Player", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UHPComponent> ActorHP;

	UPROPERTY(VisibleAnywhere, Category = "Inventory", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInventoryComponent> InventoryComp;

	UPROPERTY(VisibleAnywhere, Category = "Statistic", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UPlayerStatsComponent> PlayerStatistic;

	UPROPERTY(VisibleAnywhere, Category = "Loot component", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USearchForPickupColliderComponent> PickupItemsComponent;

	UPROPERTY(VisibleAnywhere, Category = "Line of sight componenteeeeeee", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<ULineOfSightComponent> LineOfSightComponentt;


	UPROPERTY(EditDefaultsOnly, Category = "Player")
	TSubclassOf<UGunItemdata> TestItem;

	virtual void BeginPlay() override;
};
