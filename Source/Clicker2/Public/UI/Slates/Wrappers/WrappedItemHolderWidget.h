// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "WrappedItemHolderWidget.generated.h"

/**
 * 
 */
UCLASS()
class CLICKER2_API UWrappedItemHolderWidget : public UWidget
{
	GENERATED_BODY()

	virtual TSharedRef<SWidget> RebuildWidget() override;

	TSharedPtr<class SItemHolderCompoundWidget> ItemHolderWidget;
};
