// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject\Interface.h"
#include "IDamageable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UDamageable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CLICKER2_API IDamageable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void DealDamage(int damage, UObject* DamageDealer, bool Critical) PURE_VIRTUAL(DealDamage);

	virtual int GetHP() PURE_VIRTUAL(DealDamage, return 0;);
};
