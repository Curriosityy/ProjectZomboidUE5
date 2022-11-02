// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySystem\EnemyAnimInstance.h"

#include "EnemySystem\Enemy.h"

void UEnemyAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Character = Cast<AEnemy>(TryGetPawnOwner());
}

void UEnemyAnimInstance::UpdateAnimationValues()
{
	Speed = Character->GetVelocity().Length();
	ShouldMove = Speed > 10;
}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Character)
	{
		UpdateAnimationValues();
	}
}
