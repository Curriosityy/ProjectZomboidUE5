// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponItemData.h"
#include "ItemSystem\EquippedItem.h"
#include "EquippedWeapon.generated.h"
class UWeaponAttackComponent;
class AWeaponActor;
/**
 * 
 */
UCLASS()
class CLICKER2_API UEquippedWeapon : public UEquippedItem
{
	GENERATED_BODY()

private:
	FName SocketName;

	UPROPERTY(Transient, NonTransactional)
	TObjectPtr<USkeletalMeshComponent> PlayerSkeletalMesh;

	UPROPERTY(Transient, NonTransactional)
	TObjectPtr<UEquippedWeapon> SecondHand;

	UPROPERTY(Transient, NonTransactional)
	TObjectPtr<AWeaponActor> SpawnedObject;

	UPROPERTY(Transient, NonTransactional)
	TObjectPtr<UWeaponAttackComponent> AttackComponent;

	UPROPERTY()
	bool IsMainHand;

public:
	void Initialize(EItemType itemType, FName Socket, USkeletalMeshComponent* playerMesh, UEquippedWeapon* secondHand,
	                bool isMainHand);

	void SpawnItemAtSocketPlace(UItem* item);


	void AddWeaponComponent(UWeaponItemData* weapon);

	virtual bool AddItem(UItem* item) override;

	virtual bool RemoveItem(UItem* item) override;
};
