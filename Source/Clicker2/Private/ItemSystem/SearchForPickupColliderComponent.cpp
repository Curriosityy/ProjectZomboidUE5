// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSystem/SearchForPickupColliderComponent.h"

#include "ItemSystem/Item.h"
#include "ItemSystem/ItemActor.h"

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
		items.Add(Item->GetBaseItem());
	}
	
	return items;
}

bool USearchForPickupColliderComponent::CanAddItem(UItem* item)
{
	return true;
}

bool USearchForPickupColliderComponent::AddItem(IItemHolder* previousOwner, UItem* item)
{
	//TODO:
	//SPAWN AITEM Based on UItem
	//remove UItem from previousOwner
	return IItemHolder::AddItem(previousOwner, item);
}

bool USearchForPickupColliderComponent::RemoveItem(UItem* item)
{
	for (auto itemOnGround : OverlappedItemsOnGround)
	{
		if(itemOnGround->GetBaseItem()==item)
		{
			itemOnGround->Destroy();

			return true;
		}
	}
	
	return false;
}

float USearchForPickupColliderComponent::GetWeightOfHeldItems()
{
	float sum =0;
	
	for (auto itemOnGround : OverlappedItemsOnGround)
	{
		sum += itemOnGround->GetBaseItem()->GetItemData()->GetWeight();
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
	SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void USearchForPickupColliderComponent::OnStartOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bBFromSweep, const FHitResult& SweepResult)
{
	if(IItemHolder* itemHolder = dynamic_cast<IItemHolder*>(OtherActor))
	{
		OverlappedItemsContainers.Add(itemHolder);
		OnItemHoldersChanged.Broadcast(this);		
	}
	else if(AItemActor* itemActor = dynamic_cast<AItemActor*>(OtherActor))
	{
		OverlappedItemsOnGround.Add(itemActor);
		OnItemOnGroundUpdated.Broadcast(TScriptInterface<IItemHolder>(this));
	}
}

void USearchForPickupColliderComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(IItemHolder* itemHolder = dynamic_cast<IItemHolder*>(OtherActor))
	{
		OverlappedItemsContainers.Remove(itemHolder);
		OnItemHoldersChanged.Broadcast(this);	
	}
	else if(AItemActor* itemActor = dynamic_cast<AItemActor*>(OtherActor))
	{
		OverlappedItemsOnGround.Remove(itemActor);
		OnItemOnGroundUpdated.Broadcast(this);
	}
}

TArray<IItemHolder*> USearchForPickupColliderComponent::GetOverlappedItemsContainers()
{
	TArray<IItemHolder*> containers = TArray<IItemHolder*>();
	FCollisionQueryParams params;
	params.bDebugQuery=true;
	params.AddIgnoredActor(GetOwner());
	for (auto ItemHolder : OverlappedItemsContainers)
	{
		if(auto actor = static_cast<AActor*>(ItemHolder->_getUObject()))
		{
			params.AddIgnoredActor(actor);
		}
		else if(auto comp = static_cast<UPrimitiveComponent*>(ItemHolder->_getUObject()))
		{
			params.AddIgnoredActor(comp->GetOwner());
		}
	}

	for (auto ItemHolder : OverlappedItemsContainers)
	{
		if(auto actor = static_cast<AActor*>(ItemHolder->_getUObject()))
		{
			if(GetWorld()->LineTraceTestByChannel(
				actor->GetTransform().GetLocation(),
				GetOwner()->GetTransform().GetLocation(),
				ECC_Camera,
				params))
			{
				containers.Add(ItemHolder);
			}

			DrawDebugLine(GetWorld(),actor->GetTransform().GetLocation(),GetOwner()->GetTransform().GetLocation(),FColor::Red);
		}
		else if(auto comp = static_cast<UPrimitiveComponent*>(ItemHolder->_getUObject()))
		{
			if(GetWorld()->LineTraceTestByChannel(
				comp->GetOwner()->GetTransform().GetLocation(),
				GetOwner()->GetTransform().GetLocation(),
				ECC_Camera,
				params))
			{
				containers.Add(ItemHolder);
			}

			DrawDebugLine(GetWorld(),comp->GetOwner()->GetTransform().GetLocation(),GetOwner()->GetTransform().GetLocation(),FColor::Red);
		}
	}
	
	
	return containers;
}

void USearchForPickupColliderComponent::BeginPlay()
{
	Super::BeginPlay();
	OnComponentBeginOverlap.AddDynamic(this,&USearchForPickupColliderComponent::OnStartOverlap);
	OnComponentEndOverlap.AddDynamic(this,&USearchForPickupColliderComponent::OnEndOverlap);
	
}
