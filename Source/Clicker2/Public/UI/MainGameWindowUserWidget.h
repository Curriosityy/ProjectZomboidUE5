// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MouseBlocker.h"
#include "Blueprint\UserWidget.h"
#include "MainGameWindowUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class CLICKER2_API UMainGameWindowUserWidget : public UUserWidget, public IMouseBlocker
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	class UDragWindowUserWidget* DragWidget;

	UPROPERTY(meta=(BindWidget))
	class UBorder* Border;

	UPROPERTY(meta=(BindWidget))
	class UButton* HideButton;

	bool bMouseOver;

public:
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	                               UDragDropOperation* InOperation) override;

	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual bool IsMouseOver() override;

	virtual void NativeConstruct() override;

protected:
	UFUNCTION()
	virtual void Show();

	UFUNCTION()
	virtual void Hide();
};
