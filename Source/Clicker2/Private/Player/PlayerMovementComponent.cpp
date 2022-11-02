// Fill out your copyright notice in the Description page of Project Settings.


#include "Player\PlayerMovementComponent.h"

UPlayerMovementComponent::UPlayerMovementComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	MyCustomMovementModes = MYMOVE_None;
	SlowWalkSpeedMultiplicator = .5f;
	SprintSpeedMultiplicator = 2;
}

float UPlayerMovementComponent::GetMaxSpeed() const
{
	float speedMultiplicator = 1;


	switch (MyCustomMovementModes)
	{
	case MYMOVE_Sprint:
		speedMultiplicator = SprintSpeedMultiplicator;
		break;
	case MYMOVE_SlowWalk:
		speedMultiplicator = SlowWalkSpeedMultiplicator;
		break;
	}


	return Super::GetMaxSpeed() * speedMultiplicator;
}

void UPlayerMovementComponent::SetMovementMode(EMovementMode NewMovementMode, uint8 NewCustomMode)
{
	if (NewMovementMode == MOVE_Falling)
	{
		NewCustomMode = 0;
	}

	const uint8 PrevCustomMode = MyCustomMovementModes;
	MyCustomMovementModes = static_cast<EMyMovementModes>(NewCustomMode);

	if (PrevCustomMode != MyCustomMovementModes)
	{
		OnMovementModeChanged(MovementMode, PrevCustomMode);
	}

	Super::SetMovementMode(NewMovementMode, NewCustomMode);
}
