// Fill out your copyright notice in the Description page of Project Settings.


#include "Player\Character2DAnimInstance.h"
#include "KismetAnimationLibrary.h"
#include "Player\Clicker2Character.h"

UCharacter2DAnimInstance::UCharacter2DAnimInstance()
{
	ShouldMove = false;
	Speed = 0;
	Direction = false;
}

void UCharacter2DAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UCharacter2DAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Character = Cast<AClicker2Character>(TryGetPawnOwner());
}

void UCharacter2DAnimInstance::UpdateAnimationValues()
{
	Speed = Character->GetVelocity().Length();
	ShouldMove = Speed > 10;
	Direction = UKismetAnimationLibrary::CalculateDirection(Character->GetVelocity(), Character->GetActorRotation());
}

void UCharacter2DAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Character)
	{
		UpdateAnimationValues();
	}
}
