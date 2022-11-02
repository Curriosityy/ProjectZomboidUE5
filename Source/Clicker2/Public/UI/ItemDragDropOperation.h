// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint\DragDropOperation.h"
#include "ItemDragDropOperation.generated.h"
class UItem;
/**
 * 
 */
UCLASS()
class CLICKER2_API UItemDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:
	bool bIsDragFromQuickWidget;

	UItem* GetItemPayload();
};
