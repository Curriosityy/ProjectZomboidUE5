// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Clicker2PlayerController.generated.h"

class AClicker2Character;
class UPlayerMovementComponent;
/** Forward declaration to improve compiling times */
class UNiagaraSystem;

UCLASS()
class AClicker2PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AClicker2PlayerController();

protected:
	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;

	UFUNCTION()
	void OpenInventory();

	void MoveForward(float scale);
	void MoveRight(float scale);
	void StartWalk();
	void StartSprint();
	void StopSprint();
	void StopWalk();
	void StartFiree();
	void StopFire();
	void RotateToMousePointer();
	void Search();
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	// End PlayerController interface
private:
	bool IsSprinting;
	bool IsWalking;
	EMovementMode oldMovementType;
	
	UPROPERTY(Transient, DuplicateTransient)
	TObjectPtr<UPlayerMovementComponent> PlayerMovementComponent;

	UPROPERTY(Transient, DuplicateTransient)
	TObjectPtr<AClicker2Character> PlayerCharacter;

	UPROPERTY(VisibleAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectArray;
};
