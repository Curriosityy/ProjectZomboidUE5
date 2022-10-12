// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSystem/InventoryComponent.h"

#include "macros.h"
#include "Player/Clicker2Character.h"
#include "ItemSystem/EquippedItem.h"
#include "ItemSystem/BasicItemContainer.h"
#include "ItemSystem/ItemDatas/ItemData.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Backpack = CreateDefaultSubobject<UEquippedItem>(TEXT("BackpackPlace"));
	Backpack->Initialize(EItemType::Backpack);

	HelmetPlace = CreateDefaultSubobject<UEquippedItem>(TEXT("HelmetPlace"));
	HelmetPlace->Initialize(EItemType::Helmet);

	ArmorPlace = CreateDefaultSubobject<UEquippedItem>(TEXT("ArmorPlace"));
	ArmorPlace->Initialize(EItemType::Armor);

	LeftHand = CreateDefaultSubobject<UEquippedItem>(TEXT("LeftHandPlace"));
	LeftHand->Initialize(EItemType::LeftHand);
	
	RightHand = CreateDefaultSubobject<UEquippedItem>(TEXT("RightHandPlace"));
	RightHand->Initialize(EItemType::RightHand);

	Legs = CreateDefaultSubobject<UEquippedItem>(TEXT("LegsPlace"));
	Legs->Initialize(EItemType::Legs);

	Boots = CreateDefaultSubobject<UEquippedItem>(TEXT("BootsPlace"));
	Boots->Initialize(EItemType::Boots);

	HeldItems = CreateDefaultSubobject<UBasicItemContainer>(TEXT("HeldItems"));
	HeldItems->Initialize(GetOwner<AClicker2Character>());
	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


UEquippedItem* UInventoryComponent::GetBackpack() const
{
	return Backpack;
}

UEquippedItem* UInventoryComponent::GetHelmetPlace() const
{
	return HelmetPlace;
}

UEquippedItem* UInventoryComponent::GetArmorPlace() const
{
	return ArmorPlace;
}

UEquippedItem* UInventoryComponent::GetLeftHand() const
{
	return LeftHand;
}

UEquippedItem* UInventoryComponent::GetRightHand() const
{
	return RightHand;
}

UEquippedItem* UInventoryComponent::GetLegs() const
{
	return Legs;
}

UEquippedItem* UInventoryComponent::GetBoots() const
{
	return Boots;
}

UBasicItemContainer* UInventoryComponent::GetHeldItems() const
{
	return HeldItems;
}
