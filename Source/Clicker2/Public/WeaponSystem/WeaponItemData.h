// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemSystem/ItemDatas/ItemData.h"
#include "WeaponItemData.generated.h"

class UWeaponAttackComponent;
UENUM(BlueprintType)
enum class WeaponAttackType : uint8
{
	None = 0 UMETA(Hidden),
	Meele = 1,
	Ranged = 2,
};

/**
 * 
 */
UCLASS()
class CLICKER2_API UWeaponItemData : public UItemData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	float Range;
	
	UPROPERTY(EditDefaultsOnly)
	bool TwoHanded;
	
	UPROPERTY(EditDefaultsOnly)
	WeaponAttackType AttackType;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UWeaponAttackComponent> WeaponAttackComponent;

public:
	TSubclassOf<UWeaponAttackComponent> GetWeaponAttackComponent() const;

	UWeaponItemData();
	float GetRange() const;
	bool IsTwoHanded() const;
};
