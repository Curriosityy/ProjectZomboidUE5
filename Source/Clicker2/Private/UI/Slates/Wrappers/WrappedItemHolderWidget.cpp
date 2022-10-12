// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Slates/Wrappers/WrappedItemHolderWidget.h"

#include "Widgets/DeclarativeSyntaxSupport.h"
#include "UI/Slates/SItemHolderCompoundWidget.h"

TSharedRef<SWidget> UWrappedItemHolderWidget::RebuildWidget()
{
	ItemHolderWidget = SNew(SItemHolderCompoundWidget);

	return ItemHolderWidget.ToSharedRef();
}
