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
/**
 *
 * 
 */
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
	TObjectPtr<UTexture2D> EmptySlot;

	UPROPERTY(Transient, NonTransactional)
	TObjectPtr<UItem> HeldItem = nullptr;

	UPROPERTY(Transient, NonTransactional)
	TScriptInterface<IItemHolder> ItemHolder = nullptr;

public:
	TObjectPtr<UItem> GetHeldItem() const;

	IItemHolder* GetItemHolder();

protected:
	int Index;

public:
	inline static bool sIsDragged = false;

	void SetItem(IItemHolder* itemHolder);

	UFUNCTION()
	void SetItem(TScriptInterface<IItemHolder> itemHolderScriptInterface);

	void SetCount(int count);

	void Init(int index);

	static bool IsDragged() { return sIsDragged; };

	virtual void NativeOnInitialized() override;

	virtual void NativePreConstruct() override;

protected:
	void SetIcon(UTexture2D* texture);

	void SetValues(UTexture2D* texture, int count = 1);

public:
	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	                                  UDragDropOperation*& OutOperation) override;

	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	                          UDragDropOperation* InOperation) override;

	virtual void SetVisibility(ESlateVisibility InVisibility) override;

	void DragFinished();
};
