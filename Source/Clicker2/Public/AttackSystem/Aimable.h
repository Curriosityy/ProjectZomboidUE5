// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject\Interface.h"
#include "Aimable.generated.h"

class IDamageable;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAimable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CLICKER2_API IAimable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UMeshComponent* GetAimableMesh() PURE_VIRTUAL(GetAimableMesh, return nullptr;);

	virtual IDamageable* GetDamageable() PURE_VIRTUAL(GetDamageable, return nullptr;);

	//IF PVP is off player can not be Aimed even if is Aimable
	virtual bool CanBeAimed() { return true; };
};
