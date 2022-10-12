// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemActor.generated.h"

class UItem;
UCLASS()
class CLICKER2_API AItemActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItemActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Setup(UItem* BaseItem);
	UItem* GetBaseItem() const;

private:
	UPROPERTY(VisibleAnywhere, Transient, NonTransactional)
	TObjectPtr<UItem> BaseItem;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
};
