// Fill out your copyright notice in the Description page of Project Settings.


#include "UI\DragWindowUserWidget.h"

#include <string>
#include "InputCore.h"
#include "macros.h"
#include "Blueprint\WidgetLayoutLibrary.h"
#include "Components\CanvasPanelSlot.h"

FReply UDragWindowUserWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		FVector2D mousePosition;
		GEngine->GameViewport->GetMousePosition(mousePosition);
		float scale = UWidgetLayoutLibrary::GetViewportScale(GetWorld());
		MouseOffset = (InGeometry.GetAbsolutePositionAtCoordinates(FVector2D::Zero())) - InMouseEvent.
			GetScreenSpacePosition();
		drag = true;
	}

	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

FReply UDragWindowUserWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		drag = false;
	}
	return Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
}

void UDragWindowUserWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (drag && !InMouseEvent.GetPressedButtons().Contains(EKeys::LeftMouseButton))
	{
		drag = false;
	}

	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
}

void UDragWindowUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (drag)
	{
		if (widgetToMove != nullptr)
		{
			if (UCanvasPanelSlot* slot = dynamic_cast<UCanvasPanelSlot*>(widgetToMove->Slot.Get()))
			{
				FVector2D mousePosition;
				float scale = UWidgetLayoutLibrary::GetViewportScale(GetWorld());
				GEngine->GameViewport->GetMousePosition(mousePosition);
				mousePosition += MouseOffset;
				slot->SetPosition(mousePosition / scale);
			}
			else
			{
				PRINT_DEBUG("Component to move should have UCanvasPanelSlot not %s", *Slot->GetClass()->GetName());
			}
		}
	}

	Super::NativeTick(MyGeometry, InDeltaTime);
}
