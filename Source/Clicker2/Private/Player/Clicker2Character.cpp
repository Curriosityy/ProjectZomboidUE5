// Copyright Epic Games, Inc. All Rights Reserved.


#include "Player/Clicker2Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameMode/Clicker2GameMode.h"
#include "ItemSystem/EquippedItem.h"
#include "ItemSystem/InventoryComponent.h"
#include "ItemSystem/Item.h"
#include "ItemSystem/SearchForPickupColliderComponent.h"
#include "Player/HPComponent.h"
#include "Player/PlayerMovementComponent.h"
#include "Player/PlayerStatsComponent.h"
#include "WeaponSystem/GunItemdata.h"

AClicker2Character::AClicker2Character(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UPlayerMovementComponent>(CharacterMovementComponentName))
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel2,ECR_Ignore);
	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	ActorHP = CreateDefaultSubobject<UHPComponent>(TEXT("HP"));
	ActorHP->SetupAttachment(RootComponent);

	InventoryComp = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	PlayerStatistic = CreateDefaultSubobject<UPlayerStatsComponent>(TEXT("Stats"));
	
	PickupItemsComponent = CreateDefaultSubobject<USearchForPickupColliderComponent>(TEXT("Pickup"));
	PickupItemsComponent->SetupAttachment(RootComponent);
	//PickupCapsule->SetParams(Inventory);
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AClicker2Character::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

USearchForPickupColliderComponent* AClicker2Character::GetSearchItemComponent() const
{
	return PickupItemsComponent;
}

UInventoryComponent* AClicker2Character::GetInventoryComponent() const
{
	return InventoryComp;
}

UPlayerStatsComponent* AClicker2Character::GetStatsComponent() const
{
	return PlayerStatistic;
}

void AClicker2Character::BeginPlay()
{
	Super::BeginPlay();

	if(TestItem)
	{
		auto testItemData = GetWorld()->GetAuthGameMode<AClicker2GameMode>()->SpawnItem(TestItem.GetDefaultObject());
		InventoryComp->GetRightHand()->AddItem(nullptr, testItemData);
	}
}
