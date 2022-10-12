// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Character2DAnimInstance.generated.h"

class AClicker2Character;
/**
 * 
 */
UCLASS()
class CLICKER2_API UCharacter2DAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UCharacter2DAnimInstance();

	virtual void NativeBeginPlay() override;
	virtual void NativeInitializeAnimation() override;
	void UpdateAnimationValues();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation Properties")
	TObjectPtr<AClicker2Character> Character;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation Properties")
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation Properties")
	bool ShouldMove;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Animation Properties")
	float Direction;
};
