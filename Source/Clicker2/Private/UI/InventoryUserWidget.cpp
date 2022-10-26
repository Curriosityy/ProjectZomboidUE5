// Fill out your copyright notice in the Description page of Project Settings.


#include "UI\InventoryUserWidget.h"

#include "Components\Button.h"
#include "Components\WidgetSwitcher.h"
#include "ItemSystem\BasicItemContainer.h"
#include "ItemSystem\InventoryComponent.h"
#include "Player\Clicker2Character.h"
#include "UI\EquipmentUserWidget.h"
#include "UI\ItemHolderWidget.h"
#include "UI\PlayerStatsUserWidget.h"

void UInventoryUserWidget::Show(AClicker2Character* playerToShow)
{
	Show();
	Equipment->Setup(playerToShow->GetInventoryComponent());
	ItemHolder->Setup(playerToShow->GetInventoryComponent()->GetHeldItems());
}

void UInventoryUserWidget::Hide()
{
	Super::Hide();
}

void UInventoryUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonEquipment->OnClicked.AddDynamic(this, &UInventoryUserWidget::ShowEqTab);
	ButtonItemHolder->OnClicked.AddDynamic(this, &UInventoryUserWidget::ShowItemsTab);
	ButtonPlayerStats->OnClicked.AddDynamic(this, &UInventoryUserWidget::ShowStatTab);
}

void UInventoryUserWidget::ShowEqTab()
{
	WidgetSwitcher->SetActiveWidget(Cast<UWidget>(Equipment));
}

void UInventoryUserWidget::ShowStatTab()
{
	WidgetSwitcher->SetActiveWidget(Cast<UWidget>(PlayerStats));
}

void UInventoryUserWidget::ShowItemsTab()
{
	WidgetSwitcher->SetActiveWidget(Cast<UWidget>(ItemHolder));
}

void UInventoryUserWidget::Show()
{
	Super::Show();
}
