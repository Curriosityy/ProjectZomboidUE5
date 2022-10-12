// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class CLICKER2_API SBackpackCompoundWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SBackpackCompoundWidget)
		{
		}

		SLATE_ARGUMENT(TWeakObjectPtr<class AGameHUD>, OwningHud)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	TWeakObjectPtr<class AGameHUD> OwningHud;
};
