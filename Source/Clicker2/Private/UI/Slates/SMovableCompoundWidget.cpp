// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Slates/SMovableCompoundWidget.h"
#include "SlateOptMacros.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "UI/GameHUD.h"
#include "Widgets/Layout/SConstraintCanvas.h"
BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SMovableCompoundWidget::Construct(const FArguments& InArgs)
{
	OwningHud = InArgs._OwningHud;
	SlotToMove = InArgs._SlotToMove;
	/*
	ChildSlot
	[
		// Populate the widget
	];
	*/
}

FReply SMovableCompoundWidget::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	FVector2D mousePosition;
	GEngine->GameViewport->GetMousePosition(mousePosition);
	float scale = UWidgetLayoutLibrary::GetViewportScale(OwningHud.Get());
	MouseOffset = (SlotToMove->GetOffset().GetTopLeft() * scale) - mousePosition;

	drag = true;

	return SCompoundWidget::OnMouseButtonDown(MyGeometry, MouseEvent);
}

FReply SMovableCompoundWidget::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	drag = false;
	return SCompoundWidget::OnMouseButtonUp(MyGeometry, MouseEvent);
}

int32 SMovableCompoundWidget::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
                                      const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements,
                                      int32 LayerId,
                                      const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	if (drag)
	{
		FMargin currentPosition = SlotToMove->GetOffset();
		FVector2D mousePosition;
		GEngine->GameViewport->GetMousePosition(mousePosition);
		mousePosition += MouseOffset;

		float scale = UWidgetLayoutLibrary::GetViewportScale(OwningHud.Get());
		currentPosition.Top = (mousePosition.Y / scale);
		currentPosition.Left = (mousePosition.X / scale);

		SlotToMove->SetOffset(currentPosition);
	}


	return SCompoundWidget::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle,
	                                bParentEnabled);
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
