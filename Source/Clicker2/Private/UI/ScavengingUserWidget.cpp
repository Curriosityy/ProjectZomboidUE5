// Fill out your copyright notice in the Description page of Project Settings.


#include "UI\ScavengingUserWidget.h"

#include "Components\PanelWidget.h"
#include "ItemSystem\SearchForPickupColliderComponent.h"
#include "UI\ButtonBroadcastSelf.h"
#include "UI\ItemHolderWidget.h"

int UScavengingUserWidget::GetCurrentScavengingWindow() const
{
	return CurrentScavengingWindow;
}

void UScavengingUserWidget::SwitchScavengingTab(UButton* Sender)
{
	int oldTab = CurrentScavengingWindow;
	Buttons.Find(Sender, CurrentScavengingWindow);

	if (oldTab != CurrentScavengingWindow)
	{
		RefreshItemHolderWidget();
	}
}

void UScavengingUserWidget::RebuildItemHoldersList()
{
	ItemHolders.Reset();

	for (auto itemHolder : CurrentPickupComponent->GetOverlappedItemsContainers())
	{
		ItemHolders.Add(itemHolder->_getUObject());
	}
}

void UScavengingUserWidget::OnOverlappedContainersChanged(
	USearchForPickupColliderComponent* sender)
{
	auto currentItemHolder = ItemHolders[CurrentScavengingWindow];

	RebuildItemHoldersList();

	if (!ItemHolders.Find(currentItemHolder, CurrentScavengingWindow))
	{
		CurrentScavengingWindow = 0;
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

	for (int i = 0; i < ItemHolders.Num(); i++)
	{
		if (Buttons.Num() > i)
		{
			Buttons[i]->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			auto button = NewObject<UButtonBroadcastSelf>(this);
			Buttons.Add(button);
			ButtonsPanel->AddChild(button);
			button->OnClickedSelf.AddDynamic(this, &UScavengingUserWidget::SwitchScavengingTab);
		}
	}
}

void UScavengingUserWidget::Show()
{
	Super::Show();
}

void UScavengingUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	ButtonsPanel->ClearChildren();
}

void UScavengingUserWidget::Show(USearchForPickupColliderComponent* pickupComponent)
{
	if (CurrentPickupComponent != nullptr)
	{
		CurrentPickupComponent->GetOnItemHoldersChanged()->RemoveDynamic(
			this, &UScavengingUserWidget::OnOverlappedContainersChanged);
	}

	CurrentPickupComponent = pickupComponent;
	CurrentScavengingWindow = 0;
	RebuildItemHoldersList();
	RefreshItemHolderWidget();
	RefreshButtons();

	pickupComponent->GetOnItemHoldersChanged()->AddDynamic(this, &UScavengingUserWidget::OnOverlappedContainersChanged);

	Show();
}

void UScavengingUserWidget::RefreshItemHolderWidget()
{
	ItemHolderWidget->Setup(ItemHolders[CurrentScavengingWindow].GetInterface());
}
