// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework\CharacterMovementComponent.h"
#include "PlayerMovementComponent.generated.h"

/** Movement modes for Characters. */
UENUM(BlueprintType)
enum EMyMovementModes
{
	/** None (movement is disabled). */
	MYMOVE_None UMETA(DisplayName="None"),
	MYMOVE_Sprint UMETA(DisplayName="Sprint"),
	MYMOVE_SlowWalk UMETA(DisplayName="SlowWalk"),
};

/**
 * 
 */
UCLASS()
class CLICKER2_API UPlayerMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

protected:
	UPlayerMovementComponent(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(Category="Character Movement: Sprint", EditAnywhere, BlueprintReadWrite,
		meta=(ClampMin="0", UIMin="0"))
	float SprintSpeedMultiplicator;

	UPROPERTY(Category="Character Movement: Slow Walk", EditAnywhere, BlueprintReadWrite,
		meta=(ClampMin="0", UIMin="0"))
	float SlowWalkSpeedMultiplicator;

	EMyMovementModes MyCustomMovementModes;

public:
	virtual float GetMaxSpeed() const override;

	virtual void SetMovementMode(EMovementMode NewMovementMode, uint8 NewCustomMode) override;
};
