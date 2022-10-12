// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MultipleLayerImageAsset.generated.h"

/**
 * 
 */
UCLASS()
class CLICKER2_API UMultipleLayerImageAsset : public UObject
{
	GENERATED_BODY()

public:
	TArray<FSlateBrush> Layers;
};
