// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSystem\ItemActor.h"

#include "macros.h"
#include "GameMode\Clicker2GameMode.h"
#include "ItemSystem\Item.h"
#include "ItemSystem\ItemDatas\ItemData.h"

// Sets default values
AItemActor::AItemActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("DefaultRoot");
	SetRootComponent(Root);

	StaticMeshComponentt = CreateDefaultSubobject<UStaticMeshComponent>("DefaultStaticMesh");
	StaticMeshComponentt->SetupAttachment(GetRootComponent());
}

void AItemActor::SetCollisions(UMeshComponent* obj, bool b)
{
	obj->SetGenerateOverlapEvents(b);
	obj->SetEnableGravity(b);
	obj->SetSimulatePhysics(b);
	obj->SetEnableGravity(b);
}

void AItemActor::SetCollisionsResponse(UMeshComponent* obj)
{
	obj->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	obj->SetCollisionObjectType(ECC_GameTraceChannel2);
	obj->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	obj->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	obj->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	obj->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
	obj->SetCollisionResponseToChannel(ECC_Vehicle, ECR_Overlap);
	obj->SetCollisionResponseToChannel(ECC_Destructible, ECR_Block);
	obj->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Ignore);
}

// Called when the game starts or when spawned
void AItemActor::BeginPlay()
{
	Super::BeginPlay();

	StaticMeshComponentt->DestroyComponent();
	StaticMeshComponentt = nullptr;

	if (TestObject)
	{
		auto test = NewObject<UItemData>(this, DebugItemData);
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

	if (StaticMeshComponentt)
	{
		StaticMeshComponentt->DestroyComponent();
	}

	if (SkeletalMeshComponentt)
	{
		SkeletalMeshComponentt->DestroyComponent();
	}

	if (BaseItem->GetItemData()->IsStaticMesh())
	{
		StaticMeshComponentt = NewObject<UStaticMeshComponent>(this);
		StaticMeshComponentt->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
		StaticMeshComponentt->SetStaticMesh(static_cast<UStaticMesh*>(BaseItem->GetItemData()->GetItemInWorld()));
		SetCollisionsResponse(StaticMeshComponentt);
		SetCollisions(StaticMeshComponentt, true);
		StaticMeshComponentt->RegisterComponent();
	}
	else
	{
		SkeletalMeshComponentt = NewObject<USkeletalMeshComponent>(this);
		SkeletalMeshComponentt->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
		SkeletalMeshComponentt->SetSkeletalMesh(static_cast<USkeletalMesh*>(BaseItem->GetItemData()->GetItemInWorld()));
		SetCollisionsResponse(SkeletalMeshComponentt);
		SetCollisions(SkeletalMeshComponentt, true);
		SkeletalMeshComponentt->RegisterComponent();
	}
}

bool AItemActor::CanPickUp()
{
	return true;
}

UItem* AItemActor::GetItemInfo()
{
	return BaseItem;
}

UItem* AItemActor::PickUp()
{
	Destroy();
	return BaseItem;
}
