// Copyright Epic Games, Inc. All Rights Reserved.

#include "Player\Clicker2PlayerController.h"

#include "macros.h"
#include "Field\FieldSystemTypes.h"
#include "GameFramework\CharacterMovementComponent.h"
#include "GameFramework\Pawn.h"
#include "Kismet\KismetMathLibrary.h"
#include "Player\Clicker2Character.h"
#include "Player\FInputModeGameAndUIHideCursorDuringCaptureFalse.h"
#include "Player\PlayerMovementComponent.h"
#include "UI\GameHUD.h"
#include "WeaponSystem\WeaponAttackComponent.h"

#define CHECK_IS_OVER_UI() if(GetHUD<AGameHUD>()->IsMouseOverBlockUI()) return;

AClicker2PlayerController::AClicker2PlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	ObjectArray.Add(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel3));
}

void AClicker2PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);


	RotateToMousePointer();
}

void AClicker2PlayerController::OpenInventory()
{
	if (auto hud = dynamic_cast<AGameHUD*>(GetHUD()))
	{
		hud->OpenInventoryWindow(PlayerCharacter);
	}
}

void AClicker2PlayerController::MoveForward(float scale)
{
	PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorForwardVector() * scale);
}

void AClicker2PlayerController::MoveRight(float scale)
{
	PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorRightVector() * scale);
}

void AClicker2PlayerController::StartWalk()
{
	bIsSprinting = false;
	bIsWalking = true;
	PlayerMovementComponent->SetMovementMode(PlayerMovementComponent->MovementMode, MYMOVE_SlowWalk);
}

void AClicker2PlayerController::StartSprint()
{
	bIsSprinting = true;
	bIsWalking = false;
	PlayerMovementComponent->SetMovementMode(PlayerMovementComponent->MovementMode, MYMOVE_Sprint);
}

void AClicker2PlayerController::StopSprint()
{
	bIsSprinting = false;
	PlayerMovementComponent->SetMovementMode(PlayerMovementComponent->MovementMode, 0);
}

void AClicker2PlayerController::StopWalk()
{
	bIsSprinting = false;
	PlayerMovementComponent->SetMovementMode(PlayerMovementComponent->MovementMode, 0);
}

void AClicker2PlayerController::RotateToMousePointer()
{
	CHECK_IS_OVER_UI();

	FHitResult Hit;
	GetHitResultUnderCursorForObjects(ObjectArray, false, Hit);
	APawn* myPawn = GetPawn();
	auto Location = Hit.Location;
	Location.Z = myPawn->GetActorLocation().Z;

	myPawn->GetController()->SetControlRotation(
		UKismetMathLibrary::FindLookAtRotation(myPawn->GetActorLocation(), Location));
}

void AClicker2PlayerController::Search()
{
	if (auto hud = dynamic_cast<AGameHUD*>(GetHUD()))
	{
		hud->OpenScavengeWindow(PlayerCharacter);
	}
}

void AClicker2PlayerController::Attack()
{
	CHECK_IS_OVER_UI();

	auto comp = GetPawn()->FindComponentByClass<UWeaponAttackComponent>();

	if (comp)
	{
		comp->Attack();
	}
}

void AClicker2PlayerController::StartAim()
{
	CHECK_IS_OVER_UI();

	auto comp = GetPawn()->FindComponentByClass<UWeaponAttackComponent>();

	if (comp)
	{
		comp->StartAim();
	}
}

void AClicker2PlayerController::StopAim()
{
	CHECK_IS_OVER_UI();

	auto comp = GetPawn()->FindComponentByClass<UWeaponAttackComponent>();

	if (comp)
	{
		comp->StopAim();
	}
}

void AClicker2PlayerController::Quick(int id)
{
	if (auto hud = dynamic_cast<AGameHUD*>(GetHUD()))
	{
		hud->UseQuick(id, PlayerCharacter);
	}
}

void AClicker2PlayerController::Quick1()
{
	Quick(0);
}

void AClicker2PlayerController::Quick2()
{
	Quick(1);
}

void AClicker2PlayerController::Quick3()
{
	Quick(2);
}

void AClicker2PlayerController::Quick4()
{
	Quick(3);
}

void AClicker2PlayerController::Quick5()
{
	Quick(4);
}

void AClicker2PlayerController::Quick6()
{
	Quick(5);
}

void AClicker2PlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("OpenInventory", IE_Pressed, this, &AClicker2PlayerController::OpenInventory);
	InputComponent->BindAxis("MoveForward", this, &AClicker2PlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AClicker2PlayerController::MoveRight);
	InputComponent->BindAction("Sprint", IE_Pressed, this, &AClicker2PlayerController::StartSprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &AClicker2PlayerController::StopSprint);

	InputComponent->BindAction("Walk", IE_Pressed, this, &AClicker2PlayerController::StartWalk);
	InputComponent->BindAction("Walk", IE_Released, this, &AClicker2PlayerController::StopWalk);

	InputComponent->BindAction("Fire", IE_Pressed, this, &AClicker2PlayerController::Attack);

	InputComponent->BindAction("Aim", IE_Pressed, this, &AClicker2PlayerController::StartAim);
	InputComponent->BindAction("Aim", IE_Released, this, &AClicker2PlayerController::StopAim);

	InputComponent->BindAction("Search", IE_Pressed, this, &AClicker2PlayerController::Search);

	InputComponent->BindAction("Quick1", IE_Pressed, this, &AClicker2PlayerController::Quick1);
	InputComponent->BindAction("Quick2", IE_Pressed, this, &AClicker2PlayerController::Quick2);
	InputComponent->BindAction("Quick3", IE_Pressed, this, &AClicker2PlayerController::Quick3);
	InputComponent->BindAction("Quick4", IE_Pressed, this, &AClicker2PlayerController::Quick4);
	InputComponent->BindAction("Quick5", IE_Pressed, this, &AClicker2PlayerController::Quick5);
	InputComponent->BindAction("Quick6", IE_Pressed, this, &AClicker2PlayerController::Quick6);
}

void AClicker2PlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameAndUIHideCursorDuringCaptureFalse());
	PlayerMovementComponent = Cast<UPlayerMovementComponent>(GetPawn()->GetMovementComponent());
	PlayerCharacter = Cast<AClicker2Character>(GetPawn());
}
