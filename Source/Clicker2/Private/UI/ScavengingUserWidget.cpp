// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ScavengingUserWidget.h"

#include "Components/PanelWidget.h"
#include "ItemSystem/SearchForPickupColliderComponent.h"
#include "UI/ButtonBroadcastSelf.h"
#include "UI/ItemHolderWidget.h"

void UScavengingUserWidget::SwitchScavengingTab(UButton* Sender)
{
	int oldTab = CurrentWidgetIndex;
	Buttons.Find(Sender,CurrentWidgetIndex);

	if(oldTab!=CurrentWidgetIndex)
		RefreshItemHolderWidget();
}

void UScavengingUserWidget::RebuildItemHoldersList()
{
	ItemHolders.Reset();
	ItemHolders.Add(CurrentPickupComponent);

	for (auto itemHolder : CurrentPickupComponent->GetOverlappedItemsContainers())
	{
		ItemHolders.Add(itemHolder);
	}
}

void UScavengingUserWidget::OnOverlappedContainersChanged(
	USearchForPickupColliderComponent* sender)
{
	auto currentItemHolder = ItemHolders[CurrentWidgetIndex];
	
	RebuildItemHoldersList();

	if(!ItemHolders.Find(currentItemHolder,CurrentWidgetIndex))
	{
		CurrentWidgetIndex = 0;
		RefreshItemHolderWidget();
	}

	RefreshButtons();
}

void UScavengingUserWidget::RefreshButtons()
{
	for (auto Button : Buttons)
	{
		Button->SetVisibility(ESlateVisibility::Hidden);
	}

	for(int i=0;i<ItemHolders.Num();i++)
	{
		if(Buttons.Num()>i)
		{
			Buttons[i]->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			auto button = NewObject<UButtonBroadcastSelf>(this);
			Buttons.Add(button);
			ButtonsPanel->AddChild(button);
			button->OnClickedSelf.AddDynamic(this,&UScavengingUserWidget::SwitchScavengingTab);
		}
	}
}

void UScavengingUserWidget::Show(USearchForPickupColliderComponent* pickupComponent)
{
	if(CurrentPickupComponent != pickupComponent)
		pickupComponent->GetOnItemHoldersChanged()->RemoveDynamic(this,&UScavengingUserWidget::OnOverlappedContainersChanged);
	
	CurrentPickupComponent = pickupComponent;
	CurrentWidgetIndex = 0;
	RebuildItemHoldersList();
	RefreshItemHolderWidget();
	RefreshButtons();

	pickupComponent->GetOnItemHoldersChanged()->AddDynamic(this,&UScavengingUserWidget::OnOverlappedContainersChanged);
}

void UScavengingUserWidget::RefreshItemHolderWidget()
{
	ItemHolderWidget->Setup(ItemHolders[CurrentWidgetIndex]);
}
