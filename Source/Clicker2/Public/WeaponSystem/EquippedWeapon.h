// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemSystem/EquippedItem.h"
#include "EquippedWeapon.generated.h"
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
	
	UPROPERTY(Transient,NonTransactional)
	TObjectPtr<USkeletalMeshComponent> PlayerSkeletalMesh;
	
	UPROPERTY(Transient,NonTransactional)
	TObjectPtr<UEquippedWeapon> SecondHand;

	UPROPERTY(Transient,NonTransactional)
	TObjectPtr<AWeaponActor> SpawnedObject;
public:
	
	void Initialize(EItemType itemType, FName Socket, USkeletalMeshComponent* playerMesh, UEquippedWeapon* secondHand);


	virtual bool AddItem(IItemHolder* previousOwner, UItem* item) override;
	virtual bool RemoveItem(UItem* item) override;
};