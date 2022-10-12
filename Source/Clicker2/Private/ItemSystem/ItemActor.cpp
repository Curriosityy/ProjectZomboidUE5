// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSystem/ItemActor.h"
#include "ItemSystem/Item.h"
#include "ItemSystem/ItemDatas/ItemData.h"

// Sets default values
AItemActor::AItemActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("DefaultMesh");
	SetRootComponent(StaticMeshComponent);

	StaticMeshComponent->SetGenerateOverlapEvents(true);
	StaticMeshComponent->SetEnableGravity(true);
	StaticMeshComponent->SetSimulatePhysics(true);
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMeshComponent->SetCollisionObjectType(ECC_WorldDynamic);
	StaticMeshComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

// Called when the game starts or when spawned
void AItemActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItemActor::Setup(UItem* baseItem)
{
	this->BaseItem = baseItem;
	StaticMeshComponent->SetStaticMesh(BaseItem->GetItemData()->GetItemInWorld());
}

UItem* AItemActor::GetBaseItem() const
{
	return BaseItem;
}
