// Fill out your copyright notice in the Description page of Project Settings.


#include "UI\QuickEquipUserWidget.h"

#include "Components\HorizontalBox.h"
#include "ItemSystem\BasicItemContainer.h"
#include "ItemSystem\InventoryComponent.h"
#include "ItemSystem\ItemHelper.h"
#include "Player\Clicker2Character.h"
#include "UI\ItemWidget.h"

void UQuickEquipUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (QuickEquipBox && ItemWidget)
	{
		QuickEquipBox->ClearChildren();

		for (int i = 0; i < QuickEquipCount; i++)
		{
			QuickEquipBox->AddChild(NewObject<UItemWidget>(this, ItemWidget));
		}
	}
}

UItemWidget* UQuickEquipUserWidget::FindItemWidget(UItem* Item)
{
	UItemWidget* widget = nullptr;

	for (int i = 0; i < QuickEquipItemWidgets.Num(); i++)
	{
		if (QuickEquipItemWidgets[i]->GetHeldItem() == Item)
		{
			widget = QuickEquipItemWidgets[i];
			break;
		}
	}

	return widget;
}

void UQuickEquipUserWidget::OnQuickItemItemHolderChanged(UItem* Item)
{
	if (!ItemHelper::IsInventoryItemHolder(Owner, Item->GetHolder()))
	{
		RemoveQuickItem(Item);
	}
}

void UQuickEquipUserWidget::RemoveQuickItem(UItem* Item)
{
	FindItemWidget(Item)->SetItem(nullptr);
	Item->OnItemHolderChanged.RemoveDynamic(this, &UQuickEquipUserWidget::OnQuickItemItemHolderChanged);
}

void UQuickEquipUserWidget::OnItemDroped(UItemWidget* Reciver, UItem* Payload)
{
	bool isReadyToAdd = true;

	if (!ItemHelper::IsInventoryItemHolder(Owner, Payload->GetHolder()))
	{
		isReadyToAdd = ItemHelper::AddItemToNewHolder(Owner->GetInventoryComponent()->GetHeldItems(), Payload);
	}

	if (isReadyToAdd)
	{
		if (FindItemWidget(Payload))
		{
			RemoveQuickItem(Payload);
		}

		if (Reciver->GetHeldItem())
		{
			RemoveQuickItem(Reciver->GetHeldItem());
		}

		Reciver->SetItem(Payload);
		Payload->OnItemHolderChanged.AddDynamic(this, &UQuickEquipUserWidget::OnQuickItemItemHolderChanged);
	}
}

void UQuickEquipUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Owner = GetOwningPlayer()->GetPawn<AClicker2Character>();

	if (QuickEquipBox && ItemWidget)
	{
		QuickEquipBox->ClearChildren();

		for (int i = 0; i < QuickEquipCount; i++)
		{
			UItemWidget* item = NewObject<UItemWidget>(this, ItemWidget);
			QuickEquipBox->AddChild(item);
			QuickEquipItemWidgets.Add(item);
			item->SetCount(i + 1, true);
			item->SetVisibility(ESlateVisibility::Visible);
			item->OnItemDrop.AddDynamic(this, &UQuickEquipUserWidget::OnItemDroped);
		}
	}
}

void UQuickEquipUserWidget::QuickUse(int id, AClicker2Character* character)
{
	TObjectPtr<UItem> item = QuickEquipItemWidgets[id]->GetHeldItem();

	if (item)
	{
		item->Use(character);
	}
}
