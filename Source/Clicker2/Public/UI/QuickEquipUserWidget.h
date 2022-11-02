// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint\UserWidget.h"
#include "ItemSystem\Item.h"
#include "QuickEquipUserWidget.generated.h"

class UHorizontalBox;
class UItemDragDropOperation;
/**
 * 
 */
UCLASS()
class CLICKER2_API UQuickEquipUserWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UHorizontalBox> QuickEquipBox;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UItemWidget> ItemWidget;

	UPROPERTY(EditAnywhere)
	int QuickEquipCount;

	UPROPERTY(NonTransactional, Transient)
	TArray<TObjectPtr<UItemWidget>> QuickEquipItemWidgets;

	UPROPERTY(NonTransactional, Transient)
	AClicker2Character* Owner;


	virtual void NativePreConstruct() override;

	UItemWidget* FindItemWidget(UItem* Item);

	UFUNCTION()
	void OnQuickItemItemHolderChanged(UItem* Item);

	void RemoveQuickItem(UItem* Item);

	UFUNCTION()
	void OnItemDroped(UItemWidget* Reciver, UItemDragDropOperation* Payload);

	UFUNCTION()
	void RemoveQuickItem(UDragDropOperation* Operation);

	UFUNCTION()
	void OnStartDrag(UItemWidget* Sender, UItemDragDropOperation* Payload);

	virtual void NativeConstruct() override;

public:
	void QuickUse(int id, AClicker2Character* character);

	inline static FString DragTag = "QuickEquipBar";
};
