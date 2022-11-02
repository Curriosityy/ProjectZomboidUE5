// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint\UserWidget.h"
#include "DragWindowUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class CLICKER2_API UDragWindowUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	FORCEINLINE bool IsDragging() { return drag; }

private:
	bool drag;
	FVector2D MouseOffset;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UWidget> widgetToMove;
};
