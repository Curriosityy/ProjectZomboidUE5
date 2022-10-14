// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DropItemOnGroundUserWidget.generated.h"

class AClicker2Character;
class USearchForPickupColliderComponent;

/**
 * 
 */
UCLASS()
class CLICKER2_API UDropItemOnGroundUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(Transient,NonTransactional)
	TObjectPtr<AClicker2Character> CurrentCharacter;
	
	UPROPERTY(Transient,NonTransactional)
	TObjectPtr<USearchForPickupColliderComponent> SearchItemComp;

public:
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	void Setup(AClicker2Character* Character);
};
