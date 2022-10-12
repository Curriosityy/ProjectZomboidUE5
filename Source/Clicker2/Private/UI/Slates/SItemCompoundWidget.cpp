// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Slates/SItemCompoundWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SItemCompoundWidget::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SOverlay)
		.Visibility(EVisibility::Visible)
		+ SOverlay::Slot()
		  .HAlign(HAlign_Fill)
		  .VAlign(VAlign_Fill)
		[
			SNew(SImage)
		]
		+ SOverlay::Slot()
		  .HAlign(HAlign_Fill)
		  .VAlign(VAlign_Fill)
		[
			SNew(SImage)
		]
		+ SOverlay::Slot()
		  .HAlign(HAlign_Right)
		  .VAlign(VAlign_Bottom)
		[
			SNew(STextBlock)
			.Text(FText::FromString("1"))

		]
	];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
