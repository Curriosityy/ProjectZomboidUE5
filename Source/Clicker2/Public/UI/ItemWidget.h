// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint\UserWidget.h"
#include "ItemWidget.generated.h"

class IMouseBlocker;
class IItemHolder;
class UImage;
class UTextBlock;
class UItem;
class UTexture2D;
class UDragDropOperation;
class UItemDragDropOperation;
/**
 *
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FItemWidgetEvent, UItemWidget*, Sender, UItemDragDropOperation*, Payload);

UCLASS()
class CLICKER2_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> Background;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> ItemIcon;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> CountText;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UItemDragDropOperation> DragNDropOperation;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTexture2D> EmptySlot;

	UPROPERTY(Transient, NonTransactional)
	TObjectPtr<UItem> HeldItem = nullptr;

public:
	TObjectPtr<UItem> GetHeldItem() const;

	FItemWidgetEvent OnItemDrop;
	FItemWidgetEvent OnStartDrag;

protected:
	int Index;

public:
	inline static bool sIsDragged = false;

	void SetupByItemholder(IItemHolder* itemHolder);

	void SetItem(UItem* item);

	UFUNCTION()
	void SetupByItemholder(TScriptInterface<IItemHolder> itemHolderScriptInterface);

	void SetCount(int count, bool ForceToShow);

	void SetItemIndex(int index);

	static bool IsDragged() { return sIsDragged; };

	virtual void NativeOnInitialized() override;

	virtual void NativePreConstruct() override;

	void SetIcon(UTexture2D* texture);

	void SetValues(UTexture2D* texture, int count = 1);

	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	                                  UDragDropOperation*& OutOperation) override;

	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	                          UDragDropOperation* InOperation) override;

	virtual void SetVisibility(ESlateVisibility InVisibility) override;

	static void DragFinished();
};
