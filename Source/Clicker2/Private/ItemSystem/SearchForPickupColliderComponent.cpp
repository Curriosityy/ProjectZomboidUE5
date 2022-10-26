// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSystem\SearchForPickupColliderComponent.h"

#include "GameMode\Clicker2GameMode.h"
#include "ItemSystem\Item.h"
#include "ItemSystem\ItemActor.h"

int USearchForPickupColliderComponent::GetSize()
{
	return 9999;
}

EItemType USearchForPickupColliderComponent::GetHeldItemType()
{
	return EItemType::All;
}

TArray<UItem*> USearchForPickupColliderComponent::GetItems()
{
	TArray<UItem*> items = TArray<UItem*>();

	for (auto Item : OverlappedItemsOnGround)
	{
		items.Add(Item->GetItemInfo());
	}

	return items;
}

bool USearchForPickupColliderComponent::CanAddItem(UItem* item)
{
	return true;
}

bool USearchForPickupColliderComponent::AddItem(IItemHolder* previousOwner, UItem* item)
{
	if (previousOwner->RemoveItem(item))
	{
		auto spawnedItem = GetWorld()->GetAuthGameMode<AClicker2GameMode>()->SpawnItem(item, GetOwner());

		return true;
	}

	return false;
}

bool USearchForPickupColliderComponent::RemoveItem(UItem* item)
{
	for (auto itemOnGround : OverlappedItemsOnGround)
	{
		if (itemOnGround->GetItemInfo() == item)
		{
			itemOnGround->PickUp();

			return true;
		}
	}

	return false;
}

float USearchForPickupColliderComponent::GetWeightOfHeldItems()
{
	float sum = 0;

	for (auto itemOnGround : OverlappedItemsOnGround)
	{
		sum += itemOnGround->GetItemInfo()->GetItemData()->GetWeight();
	}

	return sum;
}

FOnInventoryUpdated* USearchForPickupColliderComponent::GetOnInventoryUpdated()
{
	return &OnItemOnGroundUpdated;
}

FOnItemsHolderCountChanged* USearchForPickupColliderComponent::GetOnItemHoldersChanged()
{
	return &OnItemHoldersChanged;
}

USearchForPickupColliderComponent::USearchForPickupColliderComponent()
{
	SetGenerateOverlapEvents(true);
	SetHiddenInGame(true);
	SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SetCollisionResponseToAllChannels(ECR_Ignore);
	SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap);
	SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);
}

void USearchForPickupColliderComponent::OnStartOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                                       bool bBFromSweep, const FHitResult& SweepResult)
{
	if (IItemHolder* itemHolder = dynamic_cast<IItemHolder*>(OtherActor))
	{
		OverlappedItemsContainers.Add(itemHolder->_getUObject());
		OnItemHoldersChanged.Broadcast(this);
	}

	if (IPickupable* pickupable = dynamic_cast<IPickupable*>(OtherActor))
	{
		if (pickupable->CanPickUp())
		{
			OverlappedItemsOnGround.Add(pickupable->_getUObject());
			OnItemOnGroundUpdated.Broadcast(this);
		}
		else
		{
			//TODO:Track if changed
		}
	}
}

void USearchForPickupColliderComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IItemHolder* itemHolder = dynamic_cast<IItemHolder*>(OtherActor))
	{
		OverlappedItemsContainers.Remove(itemHolder->_getUObject());
		OnItemHoldersChanged.Broadcast(this);
	}

	if (IPickupable* pickupable = dynamic_cast<IPickupable*>(OtherActor))
	{
		OverlappedItemsOnGround.Remove(pickupable->_getUObject());
		OnItemOnGroundUpdated.Broadcast(this);
	}
}

TArray<IItemHolder*> USearchForPickupColliderComponent::GetOverlappedItemsContainers()
{
	TArray<IItemHolder*> containers = TArray<IItemHolder*>();
	FCollisionQueryParams params;
	params.bDebugQuery = true;
	params.AddIgnoredActor(GetOwner());

	//Ground is also item containers
	containers.Add(this);

	for (auto ItemHolder : OverlappedItemsContainers)
	{
		if (auto actor = static_cast<AActor*>(ItemHolder->_getUObject()))
		{
			params.AddIgnoredActor(actor);
		}
		else if (auto comp = static_cast<UPrimitiveComponent*>(ItemHolder->_getUObject()))
		{
			params.AddIgnoredActor(comp->GetOwner());
		}
	}

	for (auto ItemHolder : OverlappedItemsContainers)
	{
		containers.Add(ItemHolder.GetInterface());
		//TODO, not pickup throug walls
	}


	return containers;
}

void USearchForPickupColliderComponent::BeginPlay()
{
	Super::BeginPlay();
	OnComponentBeginOverlap.AddDynamic(this, &USearchForPickupColliderComponent::OnStartOverlap);
	OnComponentEndOverlap.AddDynamic(this, &USearchForPickupColliderComponent::OnEndOverlap);
}
