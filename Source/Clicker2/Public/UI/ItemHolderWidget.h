// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint\UserWidget.h"
#include "ItemHolderWidget.generated.h"

class UButton;
class UItem;
class UInventoryComponent;
class IItemHolder;
class UItemWidget;
/**
 * 
 */
UCLASS()
class CLICKER2_API UItemHolderWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta=(BindWidget))
	UPanelWidget* ItemsPanel;

	UPROPERTY(meta=(BindWidget))
	UPanelWidget* ButtonsPanel;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UItemWidget> ItemWidget;

	UPROPERTY(VisibleAnywhere, Transient, NonTransactional)
	TArray<TObjectPtr<UItemWidget>> ItemWidgets;

	UPROPERTY(VisibleAnywhere, Transient, NonTransactional)
	TArray<UItem*> ItemsToShow;

	UPROPERTY(VisibleAnywhere, Transient, NonTransactional)
	TArray<UButton*> PaginationButtons;

	UPROPERTY(EditAnywhere, meta=(UIMin="1"))
	int ItemsOnPage;

	UPROPERTY(EditAnywhere)
	int TestItemCount;

	UPROPERTY(VisibleAnywhere, Transient, NonTransactional)
	int CurrentPage;

	UPROPERTY(Transient, NonTransactional)
	TScriptInterface<IItemHolder> CurrentItemHolder;

protected:
	UFUNCTION()
	void OnInventoryUpdated(TScriptInterface<IItemHolder> ChangedItemHolder);

	int32 GetMaxPageNumber();

	void RefreshInventoryUI();

	UFUNCTION()
	void OnPaginationClick(UButton* sender);

	void SetupPaginationButtons();

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	                          UDragDropOperation* InOperation) override;

public:
	void Setup(IItemHolder* inventoryHolder);

	UItemHolderWidget(const FObjectInitializer& ObjectInitializer);

	UFUNCTION()

	void OnItemDroped(UItemWidget* Reciver, UItem* Payload);

	virtual void NativeConstruct() override;

	virtual void NativePreConstruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
};
