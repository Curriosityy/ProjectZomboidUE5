// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation\AnimInstance.h"
#include "EnemyAnimInstance.generated.h"
class AEnemy;
/**
 * 
 */
UCLASS()
class CLICKER2_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation Properties")
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation Properties")
	TObjectPtr<AEnemy> Character;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation Properties")
	bool ShouldMove;

	virtual void NativeBeginPlay() override;

	virtual void NativeInitializeAnimation() override;

	void UpdateAnimationValues();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
