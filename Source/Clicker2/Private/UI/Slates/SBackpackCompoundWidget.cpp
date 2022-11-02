// Fill out your copyright notice in the Description page of Project Settings.


#include "UI\Slates\SBackpackCompoundWidget.h"

#include "SlateOptMacros.h"
#include "UI\Slates\SItemHolderCompoundWidget.h"
#include "Widgets\SCanvas.h"
#include "Widgets\Layout\SConstraintCanvas.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SBackpackCompoundWidget::Construct(const FArguments& InArgs)
{
	/*
	ChildSlot
	[
		// Populate the widget
	];
	*/
	SCanvas aa;
	SConstraintCanvas::FSlot* slot = nullptr;
	OwningHud = InArgs._OwningHud;
	ChildSlot
	[
		SNew(SConstraintCanvas)
		.Clipping(EWidgetClipping::ClipToBounds)
		.RenderTransformPivot(FVector2D(0, 0))
		+ SConstraintCanvas::Slot()
		  .Alignment(FVector2D(0, 0))
		  // .Anchors(FAnchors(0,0,0,0))
		  // .Offset(FMargin(0,0,0,0))
		  .AutoSize(true)

		  .Expose(slot)
		[
			SNew(SItemHolderCompoundWidget)
			.OwningHud(OwningHud)
			.Slot(slot)
		]


	];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
