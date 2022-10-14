// Copyright Epic Games, Inc. All Rights Reserved.

#include "Player/Clicker2PlayerController.h"

#include "GameFramework/Pawn.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/FInputModeGameAndUIHideCursorDuringCaptureFalse.h"
#include "Player/PlayerMovementComponent.h"
#include "Player/Clicker2Character.h"
#include "UI/GameHUD.h"

#define CHECK_IS_OVER_UI() if(GetHUD<AGameHUD>()->IsMouseOverBlockUI()) return;

AClicker2PlayerController::AClicker2PlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
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
	IsSprinting = false;
	IsWalking = true;
	PlayerMovementComponent->SetMovementMode(PlayerMovementComponent->MovementMode, MYMOVE_SlowWalk);
}

void AClicker2PlayerController::StartSprint()
{
	IsSprinting = true;
	IsWalking = false;
	PlayerMovementComponent->SetMovementMode(PlayerMovementComponent->MovementMode, MYMOVE_Sprint);
}

void AClicker2PlayerController::StopSprint()
{
	IsSprinting = false;
	PlayerMovementComponent->SetMovementMode(PlayerMovementComponent->MovementMode, 0);
}

void AClicker2PlayerController::StopWalk()
{
	IsSprinting = false;
	PlayerMovementComponent->SetMovementMode(PlayerMovementComponent->MovementMode, 0);
}

void AClicker2PlayerController::StartFiree()
{
	CHECK_IS_OVER_UI();
}

void AClicker2PlayerController::StopFire()
{
	CHECK_IS_OVER_UI();
}

void AClicker2PlayerController::RotateToMousePointer()
{
	CHECK_IS_OVER_UI();

	FHitResult Hit;
	GetHitResultUnderCursor(ECC_WorldStatic, true, Hit);
	APawn* myPawn = GetPawn();
	auto Location = Hit.Location;
	Location.Z = 0;
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

	InputComponent->BindAction("Fire", IE_Pressed, this, &AClicker2PlayerController::StartFiree);
	InputComponent->BindAction("Fire", IE_Released, this, &AClicker2PlayerController::StopFire);

	InputComponent->BindAction("Search", IE_Pressed, this, &AClicker2PlayerController::Search);
}

void AClicker2PlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameAndUIHideCursorDuringCaptureFalse());
	PlayerMovementComponent = Cast<UPlayerMovementComponent>(GetPawn()->GetMovementComponent());
	PlayerCharacter =  Cast<AClicker2Character>(GetPawn());
}