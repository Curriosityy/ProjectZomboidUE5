// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.generated.h"

class UItemUsability;

UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EItemType: uint8
{
	None = 0 UMETA(Hidden),
	Backpack = 1 << 0,
	Helmet = 1 << 1,
	Armor = 1 << 2,
	Boots = 1 << 3,
	RightHand = 1 << 4,
	LeftHand = 1 << 5,
	Legs = 1 << 6,
	Others = 1 << 7,
	All = (1 << 8) - 1,
};
ENUM_CLASS_FLAGS(EItemType);

/**
 * 
 */

UCLASS(NotPlaceable,Abstract)
class CLICKER2_API UItemData : public UDataAsset
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category="Item")
	FGuid ID;
	
	UPROPERTY(EditDefaultsOnly, Category="Item")
	FText ItemName;

	UPROPERTY(EditDefaultsOnly, Category="Item")
	FText ItemDescription;

	UPROPERTY(EditDefaultsOnly, Category="Item")
	bool Stackable;

	UPROPERTY(EditDefaultsOnly, Category="Item")
	TObjectPtr<UTexture2D> ItemThumbnail;

	UPROPERTY(EditDefaultsOnly, Category="Item")
	TObjectPtr<UStaticMesh> ItemInWorld;

	UPROPERTY(EditDefaultsOnly, Category="Usability")
	TArray<TSubclassOf<UItemUsability>> ItemUsabilities;

	UPROPERTY(EditDefaultsOnly, Category="Item")
	float Weight;

protected:
	UPROPERTY(VisibleAnywhere, Category="Item")
	EItemType ItemType;
	



public:	
	FGuid GetID() const;
	FText GetItemName() const;
	FText GetItemDescription() const;
	bool IsStackable() const;
	TObjectPtr<UTexture2D> GetItemThumbnail() const;
	TObjectPtr<UStaticMesh> GetItemInWorld() const;
	TArray<TSubclassOf<UItemUsability>> GetItemUsabilities();
	EItemType GetItemType() const;
	float GetWeight();
};


