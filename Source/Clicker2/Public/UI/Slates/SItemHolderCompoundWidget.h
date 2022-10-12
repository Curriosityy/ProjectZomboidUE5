// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Layout/SConstraintCanvas.h"


class AGameHUD;

/**
 *
 * 
 */
class CLICKER2_API SItemHolderCompoundWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SItemHolderCompoundWidget)
		{
		}

		SLATE_ARGUMENT(TWeakObjectPtr<AGameHUD>, OwningHud)
		SLATE_ARGUMENT(SConstraintCanvas::FSlot*, Slot)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */

	TWeakObjectPtr<AGameHUD> OwningHud;
	SConstraintCanvas::FSlot* Slot;
	FVector2D MouseOffset;

	void Construct(const FArguments& InArgs);


	virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect,
	                      FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle,
	                      bool bParentEnabled) const override;

private:
	bool drag = false;
};
