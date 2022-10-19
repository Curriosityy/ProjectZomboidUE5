// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickupable.h"
#include "GameFramework/Actor.h"
#include "ItemActor.generated.h"

class UItemData;
class UItem;
UCLASS()
class CLICKER2_API AItemActor : public AActor, public  IPickupable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItemActor();
	void SetCollisions(UMeshComponent* obj, bool b);

protected:
	void SetCollisions(UMeshComponent* obj);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Setup(UItem* BaseItem);
	virtual bool CanPickUp() override;
	virtual UItem* GetItemInfo() override;
	virtual UItem* PickUp() override;
	
private:
	UPROPERTY(VisibleAnywhere, Transient, NonTransactional)
	TObjectPtr<UItem> BaseItem;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UItemData> DebugItemData;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponentt;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponentt;
	
	UPROPERTY(EditAnywhere)
	bool TestObject;
};
