// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework\PlayerController.h"
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

	void RotateToMousePointer();

	void Search();

	void Attack();

	void StartAim();

	void StopAim();

	void Quick(int id);

	UFUNCTION()
	void Quick1();

	UFUNCTION()
	void Quick2();

	UFUNCTION()
	void Quick3();

	UFUNCTION()
	void Quick4();

	UFUNCTION()
	void Quick5();

	UFUNCTION()
	void Quick6();

	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;

	// End PlayerController interface
private:
	bool bIsSprinting;
	bool bIsWalking;
	bool bIsAiming;
	EMovementMode oldMovementType;

	UPROPERTY(Transient, DuplicateTransient)
	TObjectPtr<UPlayerMovementComponent> PlayerMovementComponent;

	UPROPERTY(Transient, DuplicateTransient)
	TObjectPtr<AClicker2Character> PlayerCharacter;

	UPROPERTY(VisibleAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectArray;
};
