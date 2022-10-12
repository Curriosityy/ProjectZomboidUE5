// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Slates/SItemHolderCompoundWidget.h"

#include "SlateOptMacros.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Player/FInputModeGameAndUIHideCursorDuringCaptureFalse.h"
#include "UI/GameHUD.h"
#include "UI/Slates/SMovableCompoundWidget.h"
#include "Widgets/SCanvas.h"
#include "Widgets/Layout/SUniformGridPanel.h"
#include "Widgets/Images/SImage.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SItemHolderCompoundWidget::Construct(const FArguments& InArgs)
{
	OwningHud = InArgs._OwningHud;
	Slot = InArgs._Slot;
	/*
	ChildSlot
	[
		// Populate the widget
	];
	*/
	FMargin slotsPadding = FMargin(2, 2, 2, 2);
	FSlateBrush* brush = new FSlateBrush();
	brush->TintColor = FColor::Red;


	ChildSlot
	[
		SNew(SBorder)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(FMargin(1, 0, 1, 1))
		.Clipping(EWidgetClipping::ClipToBoundsAlways)
		.BorderBackgroundColor(FColor::Red)
		.BorderImage(brush)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			  .HAlign(HAlign_Center)
			  .VAlign(VAlign_Center)
			  .AutoHeight()
			[
				SNew(SOverlay)
				+ SOverlay::Slot()
				  .VAlign(VAlign_Fill)
				  .HAlign(HAlign_Fill)
				  .Padding(FMargin())
				[

					SNew(SMovableCompoundWidget)
					.OwningHud(OwningHud)
					.SlotToMove(Slot)
				]
				+ SOverlay::Slot()
				  .VAlign(VAlign_Fill)
				  .HAlign(HAlign_Fill)
				[
					SNew(SOverlay)
					+ SOverlay::Slot()
					  .VAlign(VAlign_Center)
					  .HAlign(HAlign_Right)
					[
						SNew(SButton)
						.Text(FText::FromString(TEXT("x")))
					]
					+ SOverlay::Slot()
					  .VAlign(VAlign_Center)
					  .HAlign(HAlign_Center)
					  .Padding(FMargin(45, 10))
					[
						SNew(STextBlock)
						.Text(FText::FromString(TEXT("INVENTORY")))
						.Justification(ETextJustify::Center)
						.Visibility(EVisibility::HitTestInvisible)
					]
				]
			]
			+ SVerticalBox::Slot()
			  .HAlign(HAlign_Center)
			  .VAlign(VAlign_Center)
			  .AutoHeight()
			[

				SNew(SUniformGridPanel)
				.SlotPadding(slotsPadding)
				+ SUniformGridPanel::Slot(0, 0)
				  .VAlign(VAlign_Top)
				  .HAlign(HAlign_Left)
				[
					SNew(SImage)
							   .DesiredSizeOverride(FVector2D(100, 100))
							   .ColorAndOpacity(FColor::White)
							   .Visibility(EVisibility::Visible)
				]
				+ SUniformGridPanel::Slot(0, 1)
				  .VAlign(VAlign_Top)
				  .HAlign(HAlign_Left)
				[
					SNew(SImage)
							   .DesiredSizeOverride(FVector2D(100, 100))
							   .ColorAndOpacity(FColor::White)
							   .Visibility(EVisibility::Visible)
				]
				+ SUniformGridPanel::Slot(0, 2)
				  .VAlign(VAlign_Top)
				  .HAlign(HAlign_Left)
				[
					SNew(SImage)
							   .DesiredSizeOverride(FVector2D(100, 100))
							   .ColorAndOpacity(FColor::White)
							   .Visibility(EVisibility::Visible)
				]
				+ SUniformGridPanel::Slot(0, 3)
				  .VAlign(VAlign_Top)
				  .HAlign(HAlign_Left)
				[
					SNew(SImage)
							   .DesiredSizeOverride(FVector2D(100, 100))
							   .ColorAndOpacity(FColor::White)
							   .Visibility(EVisibility::Visible)
				]
			]
		]
	];
}

void SItemHolderCompoundWidget::OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	OwningHud->GetOwningPlayerController()->SetInputMode(FInputModeUIOnly());

	SCompoundWidget::OnMouseEnter(MyGeometry, MouseEvent);
}

void SItemHolderCompoundWidget::OnMouseLeave(const FPointerEvent& MouseEvent)
{
	OwningHud->GetOwningPlayerController()->SetInputMode(FInputModeGameAndUIHideCursorDuringCaptureFalse());

	SCompoundWidget::OnMouseLeave(MouseEvent);
}

int32 SItemHolderCompoundWidget::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
                                         const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements,
                                         int32 LayerId,
                                         const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	return SCompoundWidget::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle,
	                                bParentEnabled);
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
