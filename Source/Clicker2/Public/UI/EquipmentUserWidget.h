// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemDragDropOperation.h"
#include "Blueprint\UserWidget.h"
#include "ItemSystem\EquippedItem.h"
#include "EquipmentUserWidget.generated.h"

class UInventoryComponent;
class UItemWidget;
/**
 * 
 */
UCLASS()
class CLICKER2_API UEquipmentUserWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UItemWidget> Head;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UItemWidget> Backpack;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UItemWidget> RightHand;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UItemWidget> Chest;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UItemWidget> LeftHand;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UItemWidget> Legs;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UItemWidget> Boots;

	UPROPERTY(Transient, NonTransactional)
	TObjectPtr<UInventoryComponent> CurrentInventoryComponent;

	UFUNCTION()
	void DoubleHandWearTest(TScriptInterface<IItemHolder> ItemHolder);

	void Unsubscribe(UEquippedItem* itemHolder, UItemWidget* widget);

	void Subscribe(UEquippedItem* itemHolder, UItemWidget* itemWidget);

	void Unsubscribe(UInventoryComponent* Object);

	void Subscribe(UInventoryComponent* Object);

	UFUNCTION()
	void OnItemDrop(UItemWidget* Reciver, UItemDragDropOperation* Payload);

	virtual void NativeOnInitialized() override;

public:
	IItemHolder* GetItemHolderBasedOnItemWidget(UItemWidget* Reciver);

	void Setup(UInventoryComponent* InventoryComponent);
};
