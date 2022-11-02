// Fill out your copyright notice in the Description page of Project Settings.


#include "UI\MainGameWindowUserWidget.h"

#include "Components\Button.h"
#include "UI\DragWindowUserWidget.h"

void UMainGameWindowUserWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	bMouseOver = true;
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
}

void UMainGameWindowUserWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	bMouseOver = false;
	Super::NativeOnMouseLeave(InMouseEvent);
}

void UMainGameWindowUserWidget::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                                  UDragDropOperation* InOperation)
{
	bMouseOver = true;
	Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);
}

void UMainGameWindowUserWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent,
                                                  UDragDropOperation* InOperation)
{
	bMouseOver = false;
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);
}

FReply UMainGameWindowUserWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry,
                                                          const FPointerEvent& InMouseEvent)
{
	//Do not pass to Game input controller
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent).Handled();
}

FReply UMainGameWindowUserWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	//Do not pass to Game input controller
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent).Handled();
}

bool UMainGameWindowUserWidget::IsMouseOver()
{
	return bMouseOver | DragWidget->IsDragging();
}

void UMainGameWindowUserWidget::Show()
{
	SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UMainGameWindowUserWidget::Hide()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UMainGameWindowUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HideButton->OnClicked.AddDynamic(this, &UMainGameWindowUserWidget::Hide);
}
