// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSystem/ItemActor.h"

#include "macros.h"
#include "GameMode/Clicker2GameMode.h"
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
	StaticMeshComponent->SetEnableGravity(true);
}

// Called when the game starts or when spawned
void AItemActor::BeginPlay()
{
	Super::BeginPlay();

	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMeshComponent->SetCollisionObjectType(ECC_GameTraceChannel2);
	StaticMeshComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	StaticMeshComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	StaticMeshComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	StaticMeshComponent->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
	StaticMeshComponent->SetCollisionResponseToChannel(ECC_Vehicle, ECR_Overlap);
	StaticMeshComponent->SetCollisionResponseToChannel(ECC_Destructible, ECR_Block);
	StaticMeshComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel2,ECR_Ignore);
	
	if(TestObject)
	{
		auto test = NewObject<UItemData>(this,DebugItemData);
		Setup(GetWorld()->GetAuthGameMode<AClicker2GameMode>()->SpawnItem(test));
	}
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
