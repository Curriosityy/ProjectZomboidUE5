// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemHolder.h"
#include "Components/StaticMeshComponent.h"
#include "SearchForPickupColliderComponent.generated.h"

class AItemActor;
class UItem;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemsHolderCountChanged, USearchForPickupColliderComponent*, itemsCountUpdated);
UCLASS()
class CLICKER2_API USearchForPickupColliderComponent : public UStaticMeshComponent,public IItemHolder
{
	GENERATED_BODY()
	
public:
	virtual int GetSize() override;
	virtual EItemType GetHeldItemType() override;
	virtual TArray<UItem*> GetItems() override;
	virtual bool CanAddItem(UItem* item) override;
	virtual bool AddItem(IItemHolder* previousOwner, UItem* item) override;
	virtual bool RemoveItem(UItem* item) override;
	virtual float GetWeightOfHeldItems() override;
	virtual FOnInventoryUpdated* GetOnInventoryUpdated() override;
	FOnItemsHolderCountChanged* GetOnItemHoldersChanged();
	TArray<IItemHolder*> GetOverlappedItemsContainers();
private:

	//EVENTS
	FOnInventoryUpdated OnItemOnGroundUpdated;
	FOnItemsHolderCountChanged OnItemHoldersChanged;


	UPROPERTY(Transient, NonTransactional)
	TArray<TObjectPtr<AItemActor>> OverlappedItemsOnGround;
	
	UPROPERTY(Transient, NonTransactional)
	TArray<TObjectPtr<IItemHolder>> OverlappedItemsContainers;
	
	UFUNCTION()
	void OnStartOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bBFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	

public:
	
	USearchForPickupColliderComponent();
	virtual void BeginPlay() override;
};
