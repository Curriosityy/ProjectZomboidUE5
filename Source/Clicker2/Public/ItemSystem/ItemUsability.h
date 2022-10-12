// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemUsability.generated.h"

/**
 * 
 */
UCLASS(Abstract,Blueprintable,NotPlaceable)
class CLICKER2_API UItemUsability : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	bool useBPFirst = false;

protected:
	//Method to implement when, want to write c++ usability of item
	virtual void Use(class AClicker2Character* user) PURE_VIRTUAL(UItemUsability,);

	//Method to implement 
	UFUNCTION(BlueprintImplementableEvent)
	void BPUse(class AClicker2Character* user);

public:
	virtual void UseItem(class AClicker2Character* user) final;
};
