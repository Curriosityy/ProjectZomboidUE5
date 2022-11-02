// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components\ActorComponent.h"
#include "InventoryComponent.generated.h"


class UBasicItemContainer;
class UEquippedItem;
class UEquippedWeapon;
class IItemHolder;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CLICKER2_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UEquippedItem* GetBackpack() const;

	UEquippedItem* GetHelmetPlace() const;

	UEquippedItem* GetArmorPlace() const;

	UEquippedItem* GetLeftHand() const;

	UEquippedItem* GetRightHand() const;

	UEquippedItem* GetLegs() const;

	UEquippedItem* GetBoots() const;

	UBasicItemContainer* GetHeldItems() const;

private:
	UPROPERTY(Instanced, Transient, VisibleAnywhere, Category="EquipedItems", DisplayName="Backpack")
	TObjectPtr<UEquippedItem> Backpack;

	UPROPERTY(Instanced, Transient, VisibleAnywhere, Category="EquipedItems", DisplayName="Helmet")
	TObjectPtr<UEquippedItem> HelmetPlace;

	UPROPERTY(Instanced, Transient, VisibleAnywhere, Category="EquipedItems", DisplayName="Armor")
	TObjectPtr<UEquippedItem> ArmorPlace;

	UPROPERTY(Instanced, Transient, VisibleAnywhere, Category="EquipedItems", DisplayName="OffHand")
	TObjectPtr<UEquippedWeapon> LeftHand;

	UPROPERTY(Instanced, Transient, VisibleAnywhere, Category="EquipedItems", DisplayName="MainHand")
	TObjectPtr<UEquippedWeapon> RightHand;

	UPROPERTY(Instanced, Transient, VisibleAnywhere, Category="EquipedItems", DisplayName="Legs")
	TObjectPtr<UEquippedItem> Legs;

	UPROPERTY(Instanced, Transient, VisibleAnywhere, Category="EquipedItems", DisplayName="Boots")
	TObjectPtr<UEquippedItem> Boots;

	UPROPERTY(Instanced, Transient, VisibleAnywhere, Category="EquipedItems", DisplayName="Held Items")
	TObjectPtr<UBasicItemContainer> HeldItems;
};
